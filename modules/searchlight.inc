<?php

function extended_search_searchlight_search($filters, $extended_search) {

  $fields = $extended_search->getFields();
  
  $entity_info = entity_get_info($extended_search->target_entity_type);
  $fields_info = field_info_fields();
  
  foreach ($filters['any'] as $field_name => $value) {
    $handler = $extended_search->getFieldHandler($field_name);
    
    $field = $fields[$field_name];
    
    if ($field['field']) {
      $field_info = $fields_info[$field_name];
      
    }
    
    
    $field_info = $fields_info[$field_name];
    $base_table = 
  }

  $search_query = array();
  foreach ($filters['any']['title'] as $value) {
    $search_query['any'][] = '(@node_title ' . $value . ')';
  }
  foreach ($filters['all']['title'] as $value) {
    $search_query['all'][] = '(@node_title ' . $value . ')';
  }
  foreach ($filters['not']['title'] as $value) {
    $search_query['not'][] = '!(@node_title ' . $value . ')';
  }
  
  $full_search_query = array();
  if (isset($search_query['any'])) {
    $full_search_query[] = implode(' | ', $search_query['any']);
  }
  if (isset($search_query['all'])) {
    $full_search_query[] = implode(' ', $search_query['all']);
  }
  if (isset($search_query['not'])) {
    $full_search_query[] = implode(' ', $search_query['not']);
  }
  
  watchdog('search_query', dprint_r($full_search_query, TRUE));
  
  $options = array(
    'query' => array(
      'search' => implode(' ', $full_search_query),
    ),
  );
  
  $form_state['redirect'] = array('updates', $options);
}