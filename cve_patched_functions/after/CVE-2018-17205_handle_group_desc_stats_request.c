handle_group_desc_stats_request(struct ofconn *ofconn,
                                const struct ofp_header *request)
{
    handle_group_request(ofconn, request,
                         ofputil_decode_group_desc_request(request),
                         append_group_desc);
    return 0;
}
