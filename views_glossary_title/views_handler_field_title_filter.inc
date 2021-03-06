<?php
// $Id$

/**
 * @file
 *
 * Override a views style for views summary.
 */
class views_handler_field_title_filter extends views_handler_field {

  function option_definition() {
    $options = parent::option_definition();
    $options['filter_punctuation'] = array('default' => FALSE);
    $options['filter_numeric'] = array('default' => FALSE);
    return $options;
  }

  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);

    $form['filter_punctuation'] = array(
      '#type' => 'textfield',
      '#title' => t('Strip punctuation and strings'),
      '#description' => t('Enter characters to remove from beginning of title. Separated by spaces. Example: , . * ZONE_'),
      '#default_value' => $this->options['filter_punctuation'],
    );
    $form['filter_numeric'] = array(
      '#type' => 'checkbox',
      '#title' => t('Strip Numbers'),
      '#description' => t('If checked, leading numbers (up to 6 digits long) will be removed from title'),
      '#default_value' => $this->options['filter_numeric'],
    );
  }

  /**
   * Render the field.
   */
  function render($values) {
    $value = $values->{$this->field_alias};
    if (!empty($this->options['filter_punctuation'])) {
      $value = $this->filter_punctuation($value);
    }
    if (!empty($this->options['filter_numeric'])) {
      $value = $this->filter_numbers($value);
    }
    return $value;
  }

  /**
   * Replace leading punctuation values.
   *
   * @param string Field value.
   *
   * @return string Filtered Field value.
   */
  function filter_punctuation($value) {
    $replace = explode(' ', trim($this->options['filter_punctuation']));
    foreach ($replace as $key) {
      $value = preg_replace('/^[' . $key . ']{1,}/', '', $value);
    }
    return $value;
  }

  /**
   * Replace numbers from the beginning of the string.
   *
   * @param string Field value.
   *
   * @return string Filtered Field value.
   */
  function filter_numbers($value) {
    $value = preg_replace('/^[0-9]{1,}/', '', $value);
    return $value;
  }
}
