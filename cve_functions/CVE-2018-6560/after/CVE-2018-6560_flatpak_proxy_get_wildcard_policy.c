flatpak_proxy_get_wildcard_policy (FlatpakProxy *proxy,
                                   const char   *_name)
{
  guint policy, wildcard_policy = 0;
  char *dot;
  g_autofree char *name = g_strdup (_name);

  dot = name + strlen (name);
  while (dot)
    {
      *dot = 0;
      policy = GPOINTER_TO_INT (g_hash_table_lookup (proxy->wildcard_policy, name));
      wildcard_policy = MAX (wildcard_policy, policy);
      dot = strrchr (name, '.');
    }

  return wildcard_policy;
}
