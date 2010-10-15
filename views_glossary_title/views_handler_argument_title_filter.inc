<?php
// $Id$

/**
 * @file
 *
 * Override a views argument for Views summary.
 */
class views_handler_argument_title_filter extends views_handler_argument_string {

  function option_definition() {
    $options = parent::option_definition();
    $options['filter_punctuation'] = array('default' => '');
    $options['filter_numeric'] = array('default' => FALSE);
    $options['glossary'] = array('default' => 1);
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
   * Provide custom summary query.
   */
  function summary_query() {
    if (empty($this->definition['many to one'])) {
      $this->ensure_my_table();
    }
    else {
      $this->table_alias = $this->helper->summary_join();
    }

    if (empty($this->options['glossary'])) {
      // Add the field.
      $this->base_alias = $this->name_alias = $this->query->add_field($this->table_alias, $this->real_field);
      $this->query->set_count_field($this->table_alias, $this->real_field);
    }
    else {
      // Add the field.
      $formula = $this->get_formula();
      $this->base_alias = $this->name_alias = $this->query->add_field(NULL, $formula, $this->real_field . '_truncated');
      $this->query->set_count_field(NULL, $formula, $this->field, $this->field . '_truncated');
    }

    return $this->summary_basics(FALSE);
  }

  /**
   * Get the formula for this argument.
   *
   * Build nested trim statement.
   * Filter out numbers and selected punctuation from the glossary index.
   * MYSQL does not have any ability return results based on the first
   * alphabetical character. This trim() option is a best-option solution.
   * Users enter punctuation, and a limited number of numeric digits to
   * reduce the amount of processing time to get results.
   */
  function get_formula() {
    $trim_array = array();
    $trim_punctuation = array();
    $trim_numeric = array();

    if (!empty($this->options['filter_punctuation'])) {
      $trim_punctuation = explode(' ', $this->options['filter_punctuation']);
    }
    if (!empty($this->options['filter_numeric'])) {
      $digit = range(0, 9);
      // Trim 6 digits worth of numbers.
      // Goes through each digit and removes any numbers, then repeats.
      // Less process intensive than searching for a range 0-99,000
      // of characters.
      $trim_numeric = array_merge($digit, $digit, $digit, $digit, $digit, $digit);
    }
    $trim_array = array_merge($trim_punctuation, $trim_numeric);

    $trim_left = '';
    $trim_right = '';

    foreach ($trim_array as $key => $value) {
      $trim_left .= 'TRIM(LEADING \'' . $value . '\' FROM ';
      $trim_right .= ') ';
    }

    // Rebuild query.
    $query = "SUBSTR(" . $trim_left . "
      $this->table_alias.$this->real_field "
      . $trim_right . ", 1, " . intval($this->options['limit']) . ")";
    return $query;
  }
}
