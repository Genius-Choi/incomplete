node_get_prim_addr_ipv4h(const node_t *node)
{
  /* Don't check the ORPort or DirPort, as this function isn't port-specific,
   * and the node might have a valid IPv4 address, yet have a zero
   * ORPort or DirPort.
   */
  if (node->ri && tor_addr_is_valid_ipv4h(node->ri->addr, 0)) {
    return node->ri->addr;
  } else if (node->rs && tor_addr_is_valid_ipv4h(node->rs->addr, 0)) {
    return node->rs->addr;
  }
  return 0;
}
