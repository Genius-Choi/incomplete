flatpak_proxy_add_filter (FlatpakProxy *proxy,
                          const char   *name,
                          const char   *rule)
{
  Filter *filter;
  GList *filters, *new_filters;

  filter = filter_new (rule);
  if (g_hash_table_lookup_extended (proxy->filters,
                                    name,
                                    NULL, (void **)&filters))
    {
      new_filters = g_list_append (filters, filter);
      g_assert (new_filters == filters);
    }
  else
    {
      filters = g_list_append (NULL, filter);
      g_hash_table_insert (proxy->filters, g_strdup (name), filters);
    }
}
