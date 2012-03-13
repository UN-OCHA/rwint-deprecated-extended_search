<?php

class ExtendedSearchFieldHandlerDate extends ExtendedSearchFieldHandlerBase {  
  public function buildInput($field_name, $first = TRUE, $default_operator = NULL, $default_value = NULL) {
    $form = array();
    
    if ($first === TRUE) {
      $options = array(
        'BETWEEN||' => t('is between'),
        'BETWEEN||NOT' => t('is NOT between'),
      );
      $default = array('BETWEEN');
    }
    else {
      $options = array(
        'BETWEEN|OR|' => t('OR is between'),
        'BETWEEN|AND|NOT' => t('AND is NOT between'),
        'BETWEEN|AND|' => t('AND is between'),
        'BETWEEN|OR|NOT' => t('OR is NOT between'),
      );
      $default = array('BETWEEN|OR|');
    }
    
    $form['operator'] = array(
      '#type' => 'select',
      '#options' => $options,
      '#default_value' => isset($default_operator) ? $default_operator : $default,
      '#attributes' => array(
        'class' => array('extended-search-filter-operator'),
      ),
    );
  
    $form['value'] = array(
      '#type' => 'container',
      '#attributes' => array(
        'class' => array('extended-search-field-date', 'extended-search-filter-value'),
      ),
      'from' => array(
        '#type' => 'date',
        //'#title' => t('From'),
        '#default_value' => isset($default_value['from']) ? $default_value['from'] : NULL,
      ),
      'to' => array(
        '#type' => 'date',
        //'#title' => t('To'),
        '#title' => t('and'),
        '#default_value' => isset($default_value['to']) ? $default_value['to'] : NULL,
      ),
    );
    
    return $form;
  }
  
  public function getFilter($field_name, $field_info, $value) {
    if (is_array($value)) {
      $value = $this->getValue($field_name, $field_info, $value);
    }
    
    list($value_from, $value_to) = explode('|', $value);
    
    $display_from = gmstrftime('%d/%m/%Y', $value_from);
    $display_to = gmstrftime('%d/%m/%Y', $value_to);
    
    if (($value_from + 86399) == $value_to) {
      $display = 'on ' . $display_from;
    }
    else {
      $display = 'between ' . $display_from . ' and ' . $display_to;
    }
    
    return array(
      'display' => $display,
      'value' => $value,
    );
  }
  
  public function getFilterValue($field_name, $field_info, $value) {
    $value = explode('|', $value);
    return array(
      'from' => array_combine(array('year', 'month', 'day'), explode(' ', gmstrftime("%Y %m %d", $value[0]))),
      'to' => array_combine(array('year', 'month', 'day'), explode(' ', gmstrftime("%Y %m %d", $value[1]))),
    );
  }
  
  public function getValue($field_name, $field_info, $value) {
    $value_from = gmmktime(0, 0, 0, $value['from']['month'], $value['from']['day'], $value['from']['year']);
    $value_to = gmmktime(23, 59, 59, $value['to']['month'], $value['to']['day'], $value['to']['year']);
    return $value_from . '|' . $value_to;
  }
  
  public function getType($field_name, $field_info) {
    return 'date';
  }
}