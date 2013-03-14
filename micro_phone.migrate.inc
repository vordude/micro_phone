<?php
/**
 * Implements hook_migrate_api().
 */
function micro_phone_migrate_api() {
  return array('api' => 2);
}

/**
 * Support for the Migrate package.
 */
class MigrateMicroPhoneFieldHandler extends MigrateFieldHandler {
  public function __construct() {
    $this->registerTypes(array('micro_phone'));
  }

  public function prepare($entity, array $field_info, array $instance, array $values) {
    $arguments = array();
    if (isset($values['arguments'])) {
      $arguments = array_filter($values['arguments']);
      unset($values['arguments']);
    }
    $language = $this->getFieldLanguage($entity, $field_info, $arguments);

    // Setup the standard Field API array for saving.
    $delta = 0;
    foreach ($values as $value) {
      $return[$language][$delta] = array('format' => $value) + array_intersect_key($arguments, $field_info['columns']);
      $delta++;
    }

    return isset($return) ? $return : NULL;
  }
}