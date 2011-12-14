<?php

class ExtendedSearchFieldHandlerText extends ExtendedSearchFieldHandlerBase {
  public function buildInput($field_name) {
    return array(
      '#type' => 'textfield',
      '#maxlength' => 1024,
    );
  }
  
  
  public function getFilter($field_name, $field_info, $value) {
    return array(
      'display' => "{$value}",
      'value' => $value,
    );
  }
  
  public function getFilterValue($field_name, $field_info, $value) {
    return $value;
  }
  
  public function getValue($field_name, $field_info, $value) {
    return $value;
  }
  
  public function getType($field_name, $field_info) {
    return 'text';
  }
}