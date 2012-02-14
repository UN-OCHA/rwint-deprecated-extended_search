<?php

class ExtendedSearchFieldHandlerDate extends ExtendedSearchFieldHandlerBase {  
  public function buildInput($field_name) {
    return array(
      '#type' => 'container',
      '#attributes' => array(
        'class' => array('extended-search-field-date'),
      ),
      'from' => array(
        '#type' => 'date',
        '#title' => t('From'),
      ),
      'to' => array(
        '#type' => 'date',
        '#title' => t('To'),
      ),
    );
  }
  
  public function getFilter($field_name, $field_info, $value) {
    // If value is a string we assume its format is timestamp_from-timestamp_to.
    if (is_string($value)){
      list($value_from, $value_to) = explode('-', $value);
    }
    // Else if value['from'] is numeric we assume the format is array('from' => timestamp_from, 'to' => timestamp_to)
    elseif (is_numeric($value['from'])) {
      $value_from = $value['from'];
      $value_to = $value['to'];
    }
    // Else format is array('from' => array('day' => day, 'month' => month, 'year' => year), 'to' => array(...))
    else {
      $value_from = gmmktime(0, 0, 0, $value['from']['month'], $value['from']['day'], $value['from']['year']);
      $value_to = gmmktime(23, 59, 59, $value['to']['month'], $value['to']['day'], $value['to']['year']);      
    }
    
    $display_from = gmstrftime('%d/%m/%Y', $value_from);
    $display_to = gmstrftime('%d/%m/%Y', $value_to);
    
    if (($value_from + 86399) == $value_to) {
      $display = 'on ' . $display_from;
    }
    else {
      $display = 'from ' . $display_from . ' to ' . $display_to;
    }
    
    return array(
      'display' => $display,
      'value' => $value_from . '-' . $value_to,
    );
  }
  
  public function getFilterValue($field_name, $field_info, $value) {
    return implode('-', array_values($value));
  }
  
  public function getValue($field_name, $field_info, $value) {
    list($from, $to) = explode('-', $value);
    return array(
      'from' => $from,
      'to' => $to,
    );
  }
  
  public function getType($field_name, $field_info) {
    return 'date';
  }
}