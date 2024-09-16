ofproto_port_set_rstp(struct ofproto *ofproto, ofp_port_t ofp_port,
                      const struct ofproto_port_rstp_settings *s)
{
    struct ofport *ofport = ofproto_get_port(ofproto, ofp_port);
    if (!ofport) {
        VLOG_WARN("%s: cannot configure RSTP on nonexistent port %"PRIu32,
                ofproto->name, ofp_port);
        return ENODEV;
    }

    if (!ofproto->ofproto_class->set_rstp_port) {
        return  EOPNOTSUPP;
    }
    ofproto->ofproto_class->set_rstp_port(ofport, s);
    return 0;
}
