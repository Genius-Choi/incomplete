parse_CLONE(char *arg, struct ofpbuf *ofpacts,
             enum ofputil_protocol *usable_protocols)
{
    const size_t clone_offset = ofpacts_pull(ofpacts);
    struct ofpact_nest *clone = ofpact_put_CLONE(ofpacts);
    char *error;

    ofpbuf_pull(ofpacts, sizeof *clone);
    error = ofpacts_parse_copy(arg, ofpacts, usable_protocols, false, 0);
    /* header points to the action list */
    ofpacts->header = ofpbuf_push_uninit(ofpacts, sizeof *clone);
    clone = ofpacts->header;

    ofpact_finish_CLONE(ofpacts, &clone);
    ofpbuf_push_uninit(ofpacts, clone_offset);
    return error;
}
