<?php
/**
 * @file
 * Penton datasheet calculation functions.
 */

/**
 * Turn excel formatted columns into numeric.
 *
 * @author James Linnell james.linnell@ixxus.com
 *
 * @param object $columns
 *   The columns to be converted.
 *
 * @return mixed
 *   The columns converted.
 */
function _penton_datasheet_excel_columns_to_numeric($columns) {
  // Turn excel formatted alphebetical columns into numerical.
  $numerical = 0;
  $alphabet = array(
    'A',
    'B',
    'C',
    'D',
    'E',
    'F',
    'G',
    'H',
    'I',
    'J',
    'K',
    'L',
    'M',
    'N',
    'O',
    'P',
    'Q',
    'R',
    'S',
    'T',
    'U',
    'V',
    'W',
    'X',
    'Y',
    'Z',
  );
  $temp_columns = array();
  foreach ($columns as $alphabetical) {
    $alphabetical = trim($alphabetical);
    // Check if this is actually a letter and not a number.
    if (ctype_alpha($alphabetical) == TRUE) {
      $alphabetical = strtoupper($alphabetical);
      $alphabetical = str_split($alphabetical, 1);
      $numerical = 0;
      $length = count($alphabetical);
      for ($i = 0; $i < $length; $i++) {
        $numerical *= 26;
        foreach ($alphabet as $key => $letter) {
          if ($alphabetical[$i] == $letter) {
            $numerical = $numerical + ($key + 1);
          }
        }
      }
      $numerical--;
      array_push($temp_columns, $numerical);
    }
    else {
      array_push($temp_columns, $alphabetical);
    }
  }
  return $temp_columns;
}

/**
 * Simply turn the csv into a useable array.
 *
 * key 0 holds titles.
 * key 1 onwards holds the data.
 *
 * @author James Linnell james.linnell@ixxus.com
 *
 * @param object $fid
 *   The file object.
 *
 * @return object
 *   The csv as array.
 */
function _penton_datasheet_csv_to_array($fid) {
  $file = file_load($fid);
  $contents = file_get_contents($file->uri);
  $table_array = array();
  $array = str_getcsv($contents, "\n");
  foreach ($array as $row) {
    $row = htmlspecialchars($row, ENT_NOQUOTES);
    $row = str_getcsv($row, ",");
    if (is_array($row) && count($row) > 1) {
      array_push($table_array, $row);
    }
  }
  return $table_array;
}
