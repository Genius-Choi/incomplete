node_get_pref_orport(const node_t *node, tor_addr_port_t *ap_out)
{
  tor_assert(ap_out);

  if (node_ipv6_or_preferred(node)) {
    node_get_pref_ipv6_orport(node, ap_out);
  } else {
    /* the primary ORPort is always on IPv4 */
    node_get_prim_orport(node, ap_out);
  }
}
