ofputil_start_queue_get_config_reply(const struct ofp_header *request,
                                     struct ovs_list *replies)
{
    struct ofpbuf *reply;
    enum ofperr error;
    ofp_port_t port;
    uint32_t queue;

    error = ofputil_decode_queue_get_config_request(request, &port, &queue);
    ovs_assert(!error);

    enum ofpraw raw = ofpraw_decode_assert(request);
    switch ((int) raw) {
    case OFPRAW_OFPT10_QUEUE_GET_CONFIG_REQUEST:
        reply = ofpraw_alloc_reply(OFPRAW_OFPT10_QUEUE_GET_CONFIG_REPLY,
                                   request, 0);
        struct ofp10_queue_get_config_reply *qgcr10
            = ofpbuf_put_zeros(reply, sizeof *qgcr10);
        qgcr10->port = htons(ofp_to_u16(port));
        break;

    case OFPRAW_OFPT11_QUEUE_GET_CONFIG_REQUEST:
        reply = ofpraw_alloc_reply(OFPRAW_OFPT11_QUEUE_GET_CONFIG_REPLY,
                                   request, 0);
        struct ofp11_queue_get_config_reply *qgcr11
            = ofpbuf_put_zeros(reply, sizeof *qgcr11);
        qgcr11->port = ofputil_port_to_ofp11(port);
        break;

    case OFPRAW_OFPST14_QUEUE_DESC_REQUEST:
        reply = ofpraw_alloc_stats_reply(request, 0);
        break;

    default:
        OVS_NOT_REACHED();
    }

    ovs_list_init(replies);
    ovs_list_push_back(replies, &reply->list_node);
}
