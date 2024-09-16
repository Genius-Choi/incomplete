parse_SET_ETH_DST(char *arg, struct ofpbuf *ofpacts,
                 enum ofputil_protocol *usable_protocols OVS_UNUSED)
{
    return str_to_mac(arg, &ofpact_put_SET_ETH_DST(ofpacts)->mac);
}
