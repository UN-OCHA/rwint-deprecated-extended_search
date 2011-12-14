<?php

/**
 * Use this hook to provide a list of entity_types that can be used for extended search.
 */
function hook_extended_search_allowed_entity_types() {
  return array(
    'node' => t('Node'),
    'taxonomy_term' => t('Taxonomy Term'),
  );
}

function hook_extended_search_field_handlers() {
  $handlers = array();
  $handlers['text']['base'] = array(
    'label' => t('Text base handler'),
    'description' => t('Base handler for fields of type text'),
    'class' => 'ExtendedSearchFieldHandlerText',
    'module' => 'extended_search',
    'file' => 'handlers/extended_search_field_handler_text.inc',
  );
  return $handlers;
}