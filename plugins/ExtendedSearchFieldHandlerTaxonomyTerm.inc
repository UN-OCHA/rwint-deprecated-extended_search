<?php

class ExtendedSearchFieldHandlerTaxonomyTerm extends ExtendedSearchFieldHandlerBase {  
  public function buildInput($field_name, $first = TRUE, $default_operator = NULL, $default_value = NULL) {
    $form = array();
    
    if ($first === TRUE) {
      $options = array(
        'IN||' => t('contains'),
        'IN||NOT' => t('does NOT contain'),
      );
      $default = array('IN||');
    }
    else {
      $options = array(
        'IN|OR|' => t('OR contains'),
        'IN|AND|' => t('AND contains'),
        'IN|AND|NOT' => t('AND does NOT contain'),
        'IN|OR|NOT' => t('OR does NOT contain'),
      );
      $default = array('IN|OR|');
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
      '#type' => 'textfield',
      '#maxlength' => 1024,
      '#default_value' => isset($default_value) ? $default_value : '',
      '#autocomplete_path' => extended_search_get_autocomplete_path($this->id, $this->entity_type, $this->bundle, $field_name),
      '#attributes' => array(
        'class' => array('extended-search-filter-value'),
      ),
    );
    
    return $form;
  }
  
  public function getFilter($field_name, $field_info, $value) {
    if (is_numeric($value)) {
      $display = $this->getFilterValue($field_name, $field_info, $value);
    }
    else {
      $display = "{$value}";
    }
    
    return array(
      'display' => $display,
      'value' => $value,
    );
  }
  
  public function getValue($field_name, $field_info, $value) {
    if (!is_numeric($value)) {
      $machine_name = $this->getVocabulary($field_name);

      $vocabulary = taxonomy_vocabulary_machine_name_load($machine_name);
      
      if (isset($vocabulary->vid)) {
        $conditions = array(
          'name' => $value,
          'vid' => $vocabulary->vid,
        );
        
        $terms = taxonomy_term_load_multiple(FALSE, $conditions);

        $term = reset($terms);
      }
    }
    else {
      $term = taxonomy_term_load($value);
    }
    
    return isset($term->tid) ? $term->tid : NULL;
  }
  
  public function getFilterValue($field_name, $field_info, $value) {
    $term = taxonomy_term_load($value);
    return isset($term->name) ? $term->name : NULL;
  }
  
  public function getType($field_name, $field_info) {
    return 'taxonomy_term';
  }
  
  public function autocomplete($field_name, $string) {
    $vocabulary = $this->getVocabulary($field_name);
  
    $term = '%' . db_like($string) . '%';

    $result = db_query('
      SELECT td.name FROM {taxonomy_term_data} td
      INNER JOIN {taxonomy_vocabulary} tv 
      ON tv.vid = td.vid
      AND tv.machine_name = :vocabulary
      WHERE td.name LIKE :term
      ORDER BY td.name
      LIMIT 100',
      array(
        ':vocabulary' => $vocabulary,
        ':term' => $term,
      ))->fetchCol();
    
    $return = array();
    
    foreach ($result as $value) {
      $return[$value] = preg_replace('/(' . preg_quote($string) . ')/i', '<strong>$1</strong>', $value);
    }
    
    return $return;
  }
  
  public function getVocabulary($field_name) {
    $field_info = field_info_field($field_name);
    
    $vocabularies = array();
    foreach ($field_info['settings']['allowed_values'] as $info) {
      $vocabularies[] = $info['vocabulary'];
    }
    
    return reset($vocabularies);
  }
}