<?php
/**
 * @file
 * All jobs defined for the migrations of the Penton legacy sites.
 */

/**
 * Run a given migration.
 *
 * @param string|array $machine_name
 *   Machine name of the migration(s) to run.
 *   If there is only one migration set it to the machine name: 'Categories'.
 *   If there are several, send them as an array: array('Pictures', 'Users').
 *   Set dependencies first, for example Users relies on Pictures. Pictures will
 *   be migrated first, and User will be skipped until Pictures are done.
 *
 * @throws \Exception
 *   Exception thrown by Migrate in case of error.
 */
function penton_migrate_job_migrate($machine_name) {
  if (variable_get('init_migration', 0)) {
    // Do not run cron if initialization of migrations has not been done yet.
    if (!is_array($machine_name)) {
      $machine_name = array($machine_name);
    }
    // Do not run migrations on each cron run for more than 1000 items.
    $options = array(
      'limit' => array(
        'unit' => 'items',
        'value' => '1000',
      ),
      'feedback' => array(
        'unit' => 'items',
        'value' => '1000',
      ),
    );
    $one_go_migrations = array('Users');
    foreach ($machine_name as $key => $name) {
      // There are many duplicates in some tables with the highwater field
      // resulting in skipping some items during pauses of migrations, so we
      // want to run these in one go as it is batched anyway.
      $migration = Migration::getInstance($name);
      $current = $migration::RESULT_INCOMPLETE;
      if ($current > 999) {
        unset($options['limit']);
      }
      if (in_array($name, $one_go_migrations)) {
        unset($options['limit']);
      }
      $migration->setDisplayFunction('penton_migrate_log');
      $migration->processImport($options);
      watchdog('penton_migrate_job', 'starting migration ' . $name);
    }
  }
  else {
    watchdog('penton_migrate_job', "Migration cron jobs did not run because initialization of migration didn't happen yet.");
  }
}

/**
 * Log the migration feedback into watchdog.
 *
 * @param string $message
 *   The message to output.
 * @param string $type
 *   Type of message. Common types are 'warning', 'error', 'success' and
 *   'notice'.
 * @param bool $error
 *   Notifies it is an error message.
 *
 * @see drush_log()
 */
function penton_migrate_log($message, $type = 'notice', $error = NULL) {
  $severity = !is_null($error) ? WATCHDOG_ERROR : WATCHDOG_DEBUG;
  if (is_string($message)) {
    $message = check_plain($message);
    watchdog('penton_migrate', "$type: $message", NULL, $severity);
  }
}
