node_get_address_string(const node_t *node, char *buf, size_t len)
{
  uint32_t ipv4_addr = node_get_prim_addr_ipv4h(node);

  if (tor_addr_is_valid_ipv4h(ipv4_addr, 0)) {
    tor_addr_t addr;
    tor_addr_from_ipv4h(&addr, ipv4_addr);
    tor_addr_to_str(buf, &addr, len, 0);
  } else if (len > 0) {
    buf[0] = '\0';
  }
}
