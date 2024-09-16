rend_get_service_list(const smartlist_t* substitute_service_list)
{
  /* It is safe to cast away the const here, because
   * rend_get_service_list_mutable does not actually modify the list */
  return rend_get_service_list_mutable((smartlist_t*)substitute_service_list);
}
