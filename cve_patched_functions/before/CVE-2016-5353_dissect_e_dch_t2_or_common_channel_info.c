dissect_e_dch_t2_or_common_channel_info(tvbuff_t *tvb, packet_info *pinfo, proto_tree *tree,
                                        int offset, struct fp_info *p_fp_info,
                                        int number_of_subframes,
                                        gboolean is_common,
                                        guint16 header_crc,
                                        proto_item * header_crc_pi,
                                        void *data)
{
    int      n;
    int      pdu_no;
    guint64  total_macis_sdus;
    guint16  macis_sdus_found = 0;
    guint16  macis_pdus       = 0;
    gboolean F                = TRUE; /* We want to continue loop if get E-RNTI indication... */
    gint     bit_offset;
    proto_item *subframe_macis_descriptors_ti = NULL;
    static struct edch_t2_subframe_info subframes[16];
    guint header_length = 0;
    /* User Buffer size */
    proto_tree_add_bits_item(tree, hf_fp_edch_user_buffer_size, tvb, offset*8,
                             18, ENC_BIG_ENDIAN);
    offset += 2;

    /* Spare is in-between... */

    /* Total number of MAC-is SDUs */
    proto_tree_add_bits_ret_val(tree, hf_fp_edch_no_macid_sdus, tvb, offset*8+4,
                                12, &total_macis_sdus, ENC_BIG_ENDIAN);
    offset += 2;

    if (is_common) {
        /* E-RNTI */
        proto_tree_add_item(tree, hf_fp_edch_e_rnti, tvb, offset, 2, ENC_BIG_ENDIAN);
        offset += 2;
    }

    bit_offset = offset*8;
    /* EDCH subframe header list */
    for (n=0; n < number_of_subframes; n++) {
        guint64    subframe_number;
        guint64    no_of_macis_pdus;
        proto_item *subframe_header_ti;
        proto_tree *subframe_header_tree;

        /* Add subframe header subtree */
        subframe_header_ti = proto_tree_add_string_format(tree, hf_fp_edch_subframe_header, tvb, offset, 0,
                                                          "", "Subframe");
        subframe_header_tree = proto_item_add_subtree(subframe_header_ti, ett_fp_edch_subframe_header);

        /* Spare bit */
        bit_offset++;

        if (!is_common) {
            /* Number of HARQ Retransmissions */
            proto_tree_add_item(subframe_header_tree, hf_fp_edch_harq_retransmissions, tvb,
                                bit_offset/8, 1, ENC_BIG_ENDIAN);
            bit_offset += 4;
        }

        /* Subframe number */
        proto_tree_add_bits_ret_val(subframe_header_tree, hf_fp_edch_subframe_number, tvb,
                                    bit_offset, 3, &subframe_number, ENC_BIG_ENDIAN);
        subframes[n].subframe_number = (guint8)subframe_number;
        bit_offset += 3;

        /* Number of MAC-is PDUs */
        proto_tree_add_bits_ret_val(subframe_header_tree, hf_fp_edch_number_of_mac_is_pdus, tvb,
                                    bit_offset, 4, &no_of_macis_pdus, ENC_BIG_ENDIAN);
        bit_offset += 4;
        subframes[n].number_of_mac_is_pdus = (guint8)no_of_macis_pdus;
        macis_pdus += subframes[n].number_of_mac_is_pdus;

        /* Next 4 bits are spare for T2*/
        if (!is_common) {
            bit_offset += 4;
        }

        /* Show summary in root */
        proto_item_append_text(subframe_header_ti, " (SFN %u, %u MAC-is PDUs)",
                               subframes[n].subframe_number, subframes[n].number_of_mac_is_pdus);
        proto_item_set_len(subframe_header_ti, is_common ? 1 : 2);
    }
    offset = bit_offset / 8;


    /* MAC-is PDU descriptors for each subframe follow */
    for (n=0; n < number_of_subframes; n++) {
        proto_tree *subframe_macis_descriptors_tree;

        /* Add subframe header subtree */
        subframe_macis_descriptors_ti = proto_tree_add_string_format(tree, hf_fp_edch_macis_descriptors, tvb, offset, 0,
                                                                     "", "MAC-is descriptors (SFN %u)", subframes[n].subframe_number);
        proto_item_set_len(subframe_macis_descriptors_ti, subframes[n].number_of_mac_is_pdus*2);
        subframe_macis_descriptors_tree = proto_item_add_subtree(subframe_macis_descriptors_ti,
                                                                 ett_fp_edch_macis_descriptors);

        /* Find a sequence of descriptors for each MAC-is PDU in this subframe */
        for (pdu_no=0; pdu_no < subframes[n].number_of_mac_is_pdus; pdu_no++) {
            proto_item *f_ti = NULL;

            subframes[n].number_of_mac_is_sdus[pdu_no] = 0;

            do {
                /* Check we haven't gone past the limit */
                if (macis_sdus_found++ > total_macis_sdus) {
                    expert_add_info_format(pinfo, f_ti, &ei_fp_mac_is_sdus_miscount, "Found too many (%u) MAC-is SDUs - header said there were %u", macis_sdus_found, (guint16)total_macis_sdus);
                }

                /* LCH-ID */
                subframes[n].mac_is_lchid[pdu_no][subframes[n].number_of_mac_is_sdus[pdu_no]] = (tvb_get_guint8(tvb, offset) & 0xf0) >> 4;
                proto_tree_add_item(subframe_macis_descriptors_tree, hf_fp_edch_macis_lchid, tvb, offset, 1, ENC_BIG_ENDIAN);
                if (subframes[n].mac_is_lchid[pdu_no][subframes[n].number_of_mac_is_sdus[pdu_no]] == 15) {
                    proto_item *ti;

                    /* 4 bits of spare */
                    offset++;

                    /* E-RNTI */
                    ti = proto_tree_add_item(tree, hf_fp_edch_e_rnti, tvb, offset, 2, ENC_BIG_ENDIAN);
                    offset += 2;

                    /* This is only allowed if:
                       - it's the common case AND
                       - it's the first descriptor */
                    if (!is_common) {
                        expert_add_info(pinfo, ti, &ei_fp_e_rnti_t2_edch_frames);
                    }
                    if (subframes[n].number_of_mac_is_sdus[pdu_no] > 0) {
                        expert_add_info(pinfo, ti, &ei_fp_e_rnti_first_entry);
                    }
                    continue;
                }

                /* Length */
                subframes[n].mac_is_length[pdu_no][subframes[n].number_of_mac_is_sdus[pdu_no]] = (tvb_get_ntohs(tvb, offset) & 0x0ffe) >> 1;
                proto_tree_add_item(subframe_macis_descriptors_tree, hf_fp_edch_macis_length, tvb, offset, 2, ENC_BIG_ENDIAN);
                offset++;

                /* Flag */
                F = tvb_get_guint8(tvb, offset) & 0x01;
                f_ti = proto_tree_add_item(subframe_macis_descriptors_tree, hf_fp_edch_macis_flag, tvb, offset, 1, ENC_BIG_ENDIAN);

                subframes[n].number_of_mac_is_sdus[pdu_no]++;

                offset++;
            } while (F == 0);
        }
    }

    /* Check overall count of MAC-is SDUs */
    if (macis_sdus_found != total_macis_sdus) {
        expert_add_info_format(pinfo, subframe_macis_descriptors_ti, &ei_fp_mac_is_sdus_miscount, "Frame contains %u MAC-is SDUs - header said there would be %u!", macis_sdus_found, (guint16)total_macis_sdus);
    }
    header_length = offset;
    /* Now PDUs */
    for (n=0; n < number_of_subframes; n++) {

        /* MAC-is PDU */
        for (pdu_no=0; pdu_no < subframes[n].number_of_mac_is_pdus; pdu_no++) {
            int i;
            guint length = 0;
            umts_mac_is_info * mac_is_info = wmem_new(wmem_file_scope(), umts_mac_is_info);

            mac_is_info->number_of_mac_is_sdus = subframes[n].number_of_mac_is_sdus[pdu_no];
            DISSECTOR_ASSERT(subframes[n].number_of_mac_is_sdus[pdu_no] <= MAX_MAC_FRAMES);
            for (i = 0; i < subframes[n].number_of_mac_is_sdus[pdu_no]; i++) {
                mac_is_info->sdulength[i] = subframes[n].mac_is_length[pdu_no][i];
                mac_is_info->lchid[i] = subframes[n].mac_is_lchid[pdu_no][i];
                length += subframes[n].mac_is_length[pdu_no][i];
            }

            /* Call MAC for this PDU if configured to */
            if (preferences_call_mac_dissectors) {
                p_add_proto_data(wmem_file_scope(), pinfo, proto_umts_mac, 0, mac_is_info);
                call_dissector_with_data(mac_fdd_edch_type2_handle, tvb_new_subset_remaining(tvb, offset), pinfo, top_level_tree, data);
            }
            else {
                /* Still show data if not decoding as MAC PDU */
                proto_tree_add_item(tree, hf_fp_edch_mac_is_pdu, tvb, offset, length, ENC_NA);
            }

            /* get_mac_tsn_size in packet-umts_mac.h, gets the global_mac_tsn_size preference in umts_mac.c */
            if (get_mac_tsn_size() == MAC_TSN_14BITS) {
                offset += length + 2; /* Plus 2 bytes for TSN 14 bits and SS 2 bit. */
            } else {
                offset += length + 1; /* Plus 1 byte for TSN 6 bits and SS 2 bit. */
            }
        }
    }
    if (preferences_header_checksum) {
        verify_header_crc_edch(tvb, pinfo, header_crc_pi, header_crc, header_length);
    }
    /* Spare extension and payload CRC (optional) */
    dissect_spare_extension_and_crc(tvb, pinfo, tree,
                                    p_fp_info->dch_crc_present, offset, header_length);
}
