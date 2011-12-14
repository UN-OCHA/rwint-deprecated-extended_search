<?php

interface ExtendedSearchFieldHandlerInterface {
  public function buildInput($field_name);
  public function getFilter($field_name, $field_info, $value);
  public function getFilterValue($field_name, $field_info, $value);
  public function getValue($field_name, $field_info, $value);
  public function getType($field_name, $field_info);
}

class ExtendedSearchFieldHandlerBase implements ExtendedSearchFieldHandlerInterface {
  protected $id = '';
  protected $entity_type = '';
  protected $bundle = '';
  
  public function __construct($id, $entity_type, $bundle) {
    $this->id = $id;
    $this->entity_type = $entity_type;
    $this->bundle = $bundle;
  }
  
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