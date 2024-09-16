flatpak_proxy_get_policy (FlatpakProxy *proxy,
                          const char   *name)
{
  guint policy, wildcard_policy;

  policy = GPOINTER_TO_INT (g_hash_table_lookup (proxy->policy, name));

  wildcard_policy = flatpak_proxy_get_wildcard_policy (proxy, name);

  return MAX (policy, wildcard_policy);
}
