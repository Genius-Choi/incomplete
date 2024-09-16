handle_bundle_control(struct ofconn *ofconn, const struct ofp_header *oh)
{
    struct ofputil_bundle_ctrl_msg bctrl;
    struct ofputil_bundle_ctrl_msg reply;
    struct ofpbuf *buf;
    enum ofperr error;

    error = reject_slave_controller(ofconn);
    if (error) {
        return error;
    }

    error = ofputil_decode_bundle_ctrl(oh, &bctrl);
    if (error) {
        return error;
    }
    reply.flags = 0;
    reply.bundle_id = bctrl.bundle_id;

    switch (bctrl.type) {
    case OFPBCT_OPEN_REQUEST:
        error = ofp_bundle_open(ofconn, bctrl.bundle_id, bctrl.flags, oh);
        reply.type = OFPBCT_OPEN_REPLY;
        break;
    case OFPBCT_CLOSE_REQUEST:
        error = ofp_bundle_close(ofconn, bctrl.bundle_id, bctrl.flags);
        reply.type = OFPBCT_CLOSE_REPLY;
        break;
    case OFPBCT_COMMIT_REQUEST:
        error = do_bundle_commit(ofconn, bctrl.bundle_id, bctrl.flags);
        reply.type = OFPBCT_COMMIT_REPLY;
        break;
    case OFPBCT_DISCARD_REQUEST:
        error = ofp_bundle_discard(ofconn, bctrl.bundle_id);
        reply.type = OFPBCT_DISCARD_REPLY;
        break;

    case OFPBCT_OPEN_REPLY:
    case OFPBCT_CLOSE_REPLY:
    case OFPBCT_COMMIT_REPLY:
    case OFPBCT_DISCARD_REPLY:
        return OFPERR_OFPBFC_BAD_TYPE;
        break;
    }

    if (!error) {
        buf = ofputil_encode_bundle_ctrl_reply(oh, &reply);
        ofconn_send_reply(ofconn, buf);
    }
    return error;
}
