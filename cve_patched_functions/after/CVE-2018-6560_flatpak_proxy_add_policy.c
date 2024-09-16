flatpak_proxy_add_policy (FlatpakProxy *proxy,
                          const char   *name,
                          FlatpakPolicy policy)
{
  guint current_policy = GPOINTER_TO_INT (g_hash_table_lookup (proxy->policy, name));

  current_policy = MAX (policy, current_policy);

  g_hash_table_replace (proxy->policy, g_strdup (name), GINT_TO_POINTER (current_policy));
}
