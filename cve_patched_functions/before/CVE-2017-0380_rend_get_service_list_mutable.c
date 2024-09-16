rend_get_service_list_mutable(smartlist_t* substitute_service_list)
{
  if (substitute_service_list) {
    return substitute_service_list;
  }

  /* If no special service list is provided, then just use the global one. */

  if (BUG(!rend_service_list)) {
    /* No global HS list, which is a programmer error. */
    return NULL;
  }

  return rend_service_list;
}
