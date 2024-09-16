decode_tlv_table_mappings(struct ofpbuf *msg, unsigned int max_fields,
                             struct ovs_list *mappings)
{
    ovs_list_init(mappings);

    while (msg->size) {
        struct nx_tlv_map *nx_map;
        struct ofputil_tlv_map *map;

        nx_map = ofpbuf_pull(msg, sizeof *nx_map);
        map = xmalloc(sizeof *map);
        ovs_list_push_back(mappings, &map->list_node);

        map->option_class = ntohs(nx_map->option_class);
        map->option_type = nx_map->option_type;

        map->option_len = nx_map->option_len;
        if (map->option_len % 4 || map->option_len > TLV_MAX_OPT_SIZE) {
            VLOG_WARN_RL(&bad_ofmsg_rl,
                         "tlv table option length (%u) is not a valid option size",
                         map->option_len);
            ofputil_uninit_tlv_table(mappings);
            return OFPERR_NXTTMFC_BAD_OPT_LEN;
        }

        map->index = ntohs(nx_map->index);
        if (map->index >= max_fields) {
            VLOG_WARN_RL(&bad_ofmsg_rl,
                         "tlv table field index (%u) is too large (max %u)",
                         map->index, max_fields - 1);
            ofputil_uninit_tlv_table(mappings);
            return OFPERR_NXTTMFC_BAD_FIELD_IDX;
        }
    }

    return 0;
}
