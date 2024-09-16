ofputil_match_to_ofp11_match(const struct match *match,
                             struct ofp11_match *ofmatch)
{
    uint32_t wc = 0;

    memset(ofmatch, 0, sizeof *ofmatch);
    ofmatch->omh.type = htons(OFPMT_STANDARD);
    ofmatch->omh.length = htons(OFPMT11_STANDARD_LENGTH);

    if (!match->wc.masks.in_port.ofp_port) {
        wc |= OFPFW11_IN_PORT;
    } else {
        ofmatch->in_port = ofputil_port_to_ofp11(match->flow.in_port.ofp_port);
    }

    ofmatch->dl_src = match->flow.dl_src;
    ofmatch->dl_src_mask = eth_addr_invert(match->wc.masks.dl_src);
    ofmatch->dl_dst = match->flow.dl_dst;
    ofmatch->dl_dst_mask = eth_addr_invert(match->wc.masks.dl_dst);

    if (match->wc.masks.vlan_tci == htons(0)) {
        wc |= OFPFW11_DL_VLAN | OFPFW11_DL_VLAN_PCP;
    } else if (match->wc.masks.vlan_tci & htons(VLAN_CFI)
               && !(match->flow.vlan_tci & htons(VLAN_CFI))) {
        ofmatch->dl_vlan = htons(OFPVID11_NONE);
        wc |= OFPFW11_DL_VLAN_PCP;
    } else {
        if (!(match->wc.masks.vlan_tci & htons(VLAN_VID_MASK))) {
            ofmatch->dl_vlan = htons(OFPVID11_ANY);
        } else {
            ofmatch->dl_vlan = htons(vlan_tci_to_vid(match->flow.vlan_tci));
        }

        if (!(match->wc.masks.vlan_tci & htons(VLAN_PCP_MASK))) {
            wc |= OFPFW11_DL_VLAN_PCP;
        } else {
            ofmatch->dl_vlan_pcp = vlan_tci_to_pcp(match->flow.vlan_tci);
        }
    }

    if (!match->wc.masks.dl_type) {
        wc |= OFPFW11_DL_TYPE;
    } else {
        ofmatch->dl_type = ofputil_dl_type_to_openflow(match->flow.dl_type);
    }

    if (!(match->wc.masks.nw_tos & IP_DSCP_MASK)) {
        wc |= OFPFW11_NW_TOS;
    } else {
        ofmatch->nw_tos = match->flow.nw_tos & IP_DSCP_MASK;
    }

    if (!match->wc.masks.nw_proto) {
        wc |= OFPFW11_NW_PROTO;
    } else {
        ofmatch->nw_proto = match->flow.nw_proto;
    }

    ofmatch->nw_src = match->flow.nw_src;
    ofmatch->nw_src_mask = ~match->wc.masks.nw_src;
    ofmatch->nw_dst = match->flow.nw_dst;
    ofmatch->nw_dst_mask = ~match->wc.masks.nw_dst;

    if (!match->wc.masks.tp_src) {
        wc |= OFPFW11_TP_SRC;
    } else {
        ofmatch->tp_src = match->flow.tp_src;
    }

    if (!match->wc.masks.tp_dst) {
        wc |= OFPFW11_TP_DST;
    } else {
        ofmatch->tp_dst = match->flow.tp_dst;
    }

    if (!(match->wc.masks.mpls_lse[0] & htonl(MPLS_LABEL_MASK))) {
        wc |= OFPFW11_MPLS_LABEL;
    } else {
        ofmatch->mpls_label = htonl(mpls_lse_to_label(
                                        match->flow.mpls_lse[0]));
    }

    if (!(match->wc.masks.mpls_lse[0] & htonl(MPLS_TC_MASK))) {
        wc |= OFPFW11_MPLS_TC;
    } else {
        ofmatch->mpls_tc = mpls_lse_to_tc(match->flow.mpls_lse[0]);
    }

    ofmatch->metadata = match->flow.metadata;
    ofmatch->metadata_mask = ~match->wc.masks.metadata;

    ofmatch->wildcards = htonl(wc);
}
