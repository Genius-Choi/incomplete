rend_service_port_config_new(const char *socket_path)
{
  if (!socket_path)
    return tor_malloc_zero(sizeof(rend_service_port_config_t) + 1);

  const size_t pathlen = strlen(socket_path) + 1;
  rend_service_port_config_t *conf =
    tor_malloc_zero(sizeof(rend_service_port_config_t) + pathlen);
  memcpy(conf->unix_addr, socket_path, pathlen);
  conf->is_unix_addr = 1;
  return conf;
}
