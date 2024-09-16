parse_WRITE_ACTIONS(char *arg, struct ofpbuf *ofpacts,
                    enum ofputil_protocol *usable_protocols)
{
    size_t ofs = ofpacts_pull(ofpacts);
    struct ofpact_nest *on;
    char *error;

    /* Add a Write-Actions instruction and then pull it off. */
    ofpact_put(ofpacts, OFPACT_WRITE_ACTIONS, sizeof *on);
    ofpbuf_pull(ofpacts, sizeof *on);

    /* Parse nested actions.
     *
     * We pulled off "write-actions" and the previous actions because the
     * OFPACT_WRITE_ACTIONS is only partially constructed: its length is such
     * that it doesn't actually include the nested actions.  That means that
     * ofpacts_parse() would reject them as being part of an Apply-Actions that
     * follows a Write-Actions, which is an invalid order.  */
    error = ofpacts_parse(arg, ofpacts, usable_protocols, false,
                          OFPACT_WRITE_ACTIONS);

    /* Put the Write-Actions back on and update its length. */
    on = ofpbuf_push_uninit(ofpacts, sizeof *on);
    on->ofpact.len = ofpacts->size;

    /* Put any previous actions or instructions back on. */
    ofpbuf_push_uninit(ofpacts, ofs);

    return error;
}
