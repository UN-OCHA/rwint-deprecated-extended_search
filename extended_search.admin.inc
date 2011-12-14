<?php

/**
 * UI controller.
 */
class ExtendedSearchUIController extends EntityDefaultUIController {
  /**
   * Overrides hook_menu() defaults.
   */
  public function hook_menu() {
    $items = parent::hook_menu();
    $items[$this->path]['description'] = 'Manage extended search pages.';
    return $items;
  }
}