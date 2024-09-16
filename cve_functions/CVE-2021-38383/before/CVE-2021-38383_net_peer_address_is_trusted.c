net_peer_address_is_trusted(const char *addr)
{
  cfg_t *section;
  const char *network;
  int i;
  int n;

  if (!addr)
    return false;

  if (strncmp(addr, "::ffff:", strlen("::ffff:")) == 0)
    addr += strlen("::ffff:");

  section = cfg_getsec(cfg, "general");

  n = cfg_size(section, "trusted_networks");
  for (i = 0; i < n; i++)
    {
      network = cfg_getnstr(section, "trusted_networks", i);

      if (!network || network[0] == '\0')
	return false;

      if (strncmp(network, addr, strlen(network)) == 0)
	return true;

      if ((strcmp(network, "localhost") == 0) && (strcmp(addr, "127.0.0.1") == 0 || strcmp(addr, "::1") == 0))
	return true;

      if (strcmp(network, "any") == 0)
	return true;
    }

  return false;
}
