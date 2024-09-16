pick_datapath_id(const struct ofproto *ofproto)
{
    const struct ofport *port;

    port = ofproto_get_port(ofproto, OFPP_LOCAL);
    if (port) {
        struct eth_addr ea;
        int error;

        error = netdev_get_etheraddr(port->netdev, &ea);
        if (!error) {
            return eth_addr_to_uint64(ea);
        }
        VLOG_WARN("%s: could not get MAC address for %s (%s)",
                  ofproto->name, netdev_get_name(port->netdev),
                  ovs_strerror(error));
    }
    return ofproto->fallback_dpid;
}
