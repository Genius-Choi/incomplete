flatpak_proxy_add_wildcarded_policy (FlatpakProxy *proxy,
                                     const char   *name,
                                     FlatpakPolicy policy)
{
  g_hash_table_replace (proxy->wildcard_policy, g_strdup (name), GINT_TO_POINTER (policy));
}
