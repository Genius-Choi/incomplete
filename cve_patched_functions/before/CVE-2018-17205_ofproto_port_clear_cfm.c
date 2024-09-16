ofproto_port_clear_cfm(struct ofproto *ofproto, ofp_port_t ofp_port)
{
    struct ofport *ofport = ofproto_get_port(ofproto, ofp_port);
    if (ofport && ofproto->ofproto_class->set_cfm) {
        ofproto->ofproto_class->set_cfm(ofport, NULL);
    }
}
