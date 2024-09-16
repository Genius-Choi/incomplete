filter_list_free (GList *filters)
{
  g_list_free_full (filters, (GDestroyNotify)filter_free);
}
