<?php

class ExtendedSearchController extends EntityAPIControllerExportable {

  /**
   * Overrides create().
   */
  public function create(array $values = array()) {
    // Add values that are specific to our Model
    $values += array( 
      'entity_id' => '',
      'entity_name' => '',
      'entity_label' => '',
      'entity_description' => '',
      'target_entity_type' => '',
      'target_bundle' => '',
      'target_fields' => array(),
    );
    
    $extended_search = parent::create($values);
    return $extended_search;
  }
}