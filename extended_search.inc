<?php

class ExtendedSearchEntity extends Entity {
  protected $field_handlers = array();
  
  public function __construct(array $values = array(), $entityType = NULL) {
    parent::__construct($values, 'extended_search');
  }

  /**
   * Overrides __sleep().
   * We empty field_handlers to prevent "incomplete class" error when unserialized
   * as we use a lazy load mechanism to load field handlers.
   */
  public function __sleep() {
    $this->field_handlers = array();
    return parent::__sleep();
  }
  
  /**
   * Override buildContent() to add the username to the output.
   */
  public function buildContent($view_mode = 'full', $langcode = NULL) {
    $content['title'] = array(
      '#markup' => "Title: " . $this->label(),
    );
        
    return entity_get_controller($this->entityType)->buildContent($this, $view_mode, $langcode, $content);
  }
  
  /**
   * Specifies the default label, which is picked up by label() by default.
   */
  protected function defaultLabel() {
    return $this->entity_label;
  }

  /**
   * Specifies the default uri, which is picked up by uri() by default.
   */
  protected function defaultURI() {
    return array('path' => 'extended_search/' . $this->identifier());
  }
  
  public function getField($field_name) {
    $fields = $this->getFields();
    return isset($fields[$field_name]) ? $fields[$field_name] : NULL;
  }
  
  public function getFields() {
    return $this->target_fields;
  }
  
  public function getFieldHandler($field_name) {
    $field = $this->getField($field_name);
    if (isset($field)) {    
      $handler_id = $field['handler'];
      if (!isset($this->field_handlers[$handler_id])) {
        $handler = extended_search_get_field_handler($this->target_entity_type, $this->target_bundle, $handler_id);
        $this->field_handlers[$handler_id] = $handler;
      }
      return $this->field_handlers[$handler_id];
    }
    return NULL;
  }
  
  public function getFieldHandlers() {
    $handlers = array();
    
    foreach ($this->getFields() as $field_name => $field_info) {
      $handlers[$field_name] = $this->getFieldHandler($field_name);
    }
    
    return $handlers;
  }
}