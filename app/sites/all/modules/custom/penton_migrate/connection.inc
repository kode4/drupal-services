<?php
/**
 * @file
 * Defines legacy connection settings.
 */

// Thanks to this we don't need to explicitly write into the settings.php
// of each site.
Database::addConnectionInfo('pisces', 'default', array(
  'driver' => 'mysql',
  'database' => variable_get('penton_migrate_source_database', 'penton_legacy_waste360'),
  'username' => variable_get('penton_migrate_source_username', 'pentonuser'),
  'password' => variable_get('penton_migrate_source_password', '123'),
  'host' => variable_get('penton_migrate_source_host', 'localhost'),
  'prefix' => '',
));
