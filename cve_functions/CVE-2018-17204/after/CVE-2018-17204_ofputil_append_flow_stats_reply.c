ofputil_append_flow_stats_reply(const struct ofputil_flow_stats *fs,
                                struct ovs_list *replies,
                                const struct tun_table *tun_table)
{
    struct ofputil_flow_stats *fs_ = CONST_CAST(struct ofputil_flow_stats *,
                                                fs);
    const struct tun_table *orig_tun_table;
    struct ofpbuf *reply = ofpbuf_from_list(ovs_list_back(replies));
    size_t start_ofs = reply->size;
    enum ofp_version version = ofpmp_version(replies);
    enum ofpraw raw = ofpmp_decode_raw(replies);

    orig_tun_table = fs->match.flow.tunnel.metadata.tab;
    fs_->match.flow.tunnel.metadata.tab = tun_table;

    if (raw == OFPRAW_OFPST11_FLOW_REPLY || raw == OFPRAW_OFPST13_FLOW_REPLY) {
        struct ofp11_flow_stats *ofs;

        ofpbuf_put_uninit(reply, sizeof *ofs);
        oxm_put_match(reply, &fs->match, version);
        ofpacts_put_openflow_instructions(fs->ofpacts, fs->ofpacts_len, reply,
                                          version);

        ofs = ofpbuf_at_assert(reply, start_ofs, sizeof *ofs);
        ofs->length = htons(reply->size - start_ofs);
        ofs->table_id = fs->table_id;
        ofs->pad = 0;
        ofs->duration_sec = htonl(fs->duration_sec);
        ofs->duration_nsec = htonl(fs->duration_nsec);
        ofs->priority = htons(fs->priority);
        ofs->idle_timeout = htons(fs->idle_timeout);
        ofs->hard_timeout = htons(fs->hard_timeout);
        if (version >= OFP14_VERSION) {
            ofs->importance = htons(fs->importance);
        } else {
            ofs->importance = 0;
        }
        if (raw == OFPRAW_OFPST13_FLOW_REPLY) {
            ofs->flags = ofputil_encode_flow_mod_flags(fs->flags, version);
        } else {
            ofs->flags = 0;
        }
        memset(ofs->pad2, 0, sizeof ofs->pad2);
        ofs->cookie = fs->cookie;
        ofs->packet_count = htonll(unknown_to_zero(fs->packet_count));
        ofs->byte_count = htonll(unknown_to_zero(fs->byte_count));
    } else if (raw == OFPRAW_OFPST10_FLOW_REPLY) {
        struct ofp10_flow_stats *ofs;

        ofpbuf_put_uninit(reply, sizeof *ofs);
        ofpacts_put_openflow_actions(fs->ofpacts, fs->ofpacts_len, reply,
                                     version);
        ofs = ofpbuf_at_assert(reply, start_ofs, sizeof *ofs);
        ofs->length = htons(reply->size - start_ofs);
        ofs->table_id = fs->table_id;
        ofs->pad = 0;
        ofputil_match_to_ofp10_match(&fs->match, &ofs->match);
        ofs->duration_sec = htonl(fs->duration_sec);
        ofs->duration_nsec = htonl(fs->duration_nsec);
        ofs->priority = htons(fs->priority);
        ofs->idle_timeout = htons(fs->idle_timeout);
        ofs->hard_timeout = htons(fs->hard_timeout);
        memset(ofs->pad2, 0, sizeof ofs->pad2);
        put_32aligned_be64(&ofs->cookie, fs->cookie);
        put_32aligned_be64(&ofs->packet_count,
                           htonll(unknown_to_zero(fs->packet_count)));
        put_32aligned_be64(&ofs->byte_count,
                           htonll(unknown_to_zero(fs->byte_count)));
    } else if (raw == OFPRAW_NXST_FLOW_REPLY) {
        struct nx_flow_stats *nfs;
        int match_len;

        ofpbuf_put_uninit(reply, sizeof *nfs);
        match_len = nx_put_match(reply, &fs->match, 0, 0);
        ofpacts_put_openflow_actions(fs->ofpacts, fs->ofpacts_len, reply,
                                     version);
        nfs = ofpbuf_at_assert(reply, start_ofs, sizeof *nfs);
        nfs->length = htons(reply->size - start_ofs);
        nfs->table_id = fs->table_id;
        nfs->pad = 0;
        nfs->duration_sec = htonl(fs->duration_sec);
        nfs->duration_nsec = htonl(fs->duration_nsec);
        nfs->priority = htons(fs->priority);
        nfs->idle_timeout = htons(fs->idle_timeout);
        nfs->hard_timeout = htons(fs->hard_timeout);
        nfs->idle_age = htons(fs->idle_age < 0 ? 0
                              : fs->idle_age < UINT16_MAX ? fs->idle_age + 1
                              : UINT16_MAX);
        nfs->hard_age = htons(fs->hard_age < 0 ? 0
                              : fs->hard_age < UINT16_MAX ? fs->hard_age + 1
                              : UINT16_MAX);
        nfs->match_len = htons(match_len);
        nfs->cookie = fs->cookie;
        nfs->packet_count = htonll(fs->packet_count);
        nfs->byte_count = htonll(fs->byte_count);
    } else {
        OVS_NOT_REACHED();
    }

    ofpmp_postappend(replies, start_ofs);
    fs_->match.flow.tunnel.metadata.tab = orig_tun_table;
}
