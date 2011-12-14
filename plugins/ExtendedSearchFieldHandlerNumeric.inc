<?php

class ExtendedSearchFieldHandlerNumeric extends ExtendedSearchFieldHandlerBase {  
  public function buildInput($field_name) {    
    return array(
      '#type' => 'textfield',
      '#maxlength' => 32,
    );
  }
  
  public function getFilter($field_name, $field_info, $value) {
    return array(
      'display' => "{$value}",
      'value' => $this->convertNumericValue($field_info['type'], $value),
    );
  }
  
  public function getFilterValue($field_name, $field_info, $value) {
    return $this->convertNumericValue($field_info['type'], $value);
  }
  
  public function getValue($field_name, $field_info, $value) {
    return $this->convertNumericValue($field_info['type'], $value);
  }

  public function getType($field_name, $field_info) {
    return 'numeric';
  }
  
  private function convertNumericValue($type, $value) {
    if ($type === 'float') {
      return floatval($value);
    }
    else {
      return intval($value);
    }    
  }
}