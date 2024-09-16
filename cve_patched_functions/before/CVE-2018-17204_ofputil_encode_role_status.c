ofputil_encode_role_status(const struct ofputil_role_status *status,
                           enum ofputil_protocol protocol)
{
    enum ofp_version version;

    version = ofputil_protocol_to_ofp_version(protocol);
    if (version >= OFP14_VERSION) {
        struct ofp14_role_status *rstatus;
        struct ofpbuf *buf;

        buf = ofpraw_alloc_xid(OFPRAW_OFPT14_ROLE_STATUS, version, htonl(0),
                               0);
        rstatus = ofpbuf_put_zeros(buf, sizeof *rstatus);
        rstatus->role = htonl(status->role);
        rstatus->reason = status->reason;
        rstatus->generation_id = htonll(status->generation_id);

        return buf;
    } else {
        return NULL;
    }
}
