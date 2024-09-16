parse_actions_property(struct ofpbuf *property, enum ofp_version version,
                       struct ofpbuf *ofpacts)
{
    if (!ofpbuf_try_pull(property, ROUND_UP(ofpbuf_headersize(property), 8))) {
        VLOG_WARN_RL(&bad_ofmsg_rl, "actions property has bad length %"PRIu32,
                     property->size);
        return OFPERR_OFPBPC_BAD_LEN;
    }

    return ofpacts_pull_openflow_actions(property, property->size,
                                         version, NULL, NULL, ofpacts);
}
