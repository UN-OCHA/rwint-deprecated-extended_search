<?php

class ExtendedSearchFieldHandlerTaxonomyTerm extends ExtendedSearchFieldHandlerBase {  
  public function buildInput($field_name) {    
    return array(
      '#type' => 'textfield',
      '#maxlength' => 1024,
      '#autocomplete_path' => extended_search_get_autocomplete_path($this->id, $this->entity_type, $this->bundle, $field_name),
    );
  }
  
  public function getFilter($field_name, $field_info, $value) {
    return array(
      'display' => "{$value}",
      'value' => $value,
    );
  }
  
  public function getValue($field_name, $field_info, $value) {
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