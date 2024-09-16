ofputil_encode_requestforward(const struct ofputil_requestforward *rf,
                              enum ofputil_protocol protocol)
{
    enum ofp_version ofp_version = ofputil_protocol_to_ofp_version(protocol);
    struct ofpbuf *inner;

    switch (rf->reason) {
    case OFPRFR_GROUP_MOD:
        inner = ofputil_encode_group_mod(ofp_version, rf->group_mod);
        break;

    case OFPRFR_METER_MOD:
        inner = ofputil_encode_meter_mod(ofp_version, rf->meter_mod);
        break;

    case OFPRFR_N_REASONS:
    default:
        OVS_NOT_REACHED();
    }

    struct ofp_header *inner_oh = inner->data;
    inner_oh->xid = rf->xid;
    inner_oh->length = htons(inner->size);

    struct ofpbuf *outer = ofpraw_alloc_xid(OFPRAW_OFPT14_REQUESTFORWARD,
                                            ofp_version, htonl(0),
                                            inner->size);
    ofpbuf_put(outer, inner->data, inner->size);
    ofpbuf_delete(inner);

    return outer;
}
