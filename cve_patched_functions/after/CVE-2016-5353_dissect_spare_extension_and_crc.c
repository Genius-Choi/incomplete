dissect_spare_extension_and_crc(tvbuff_t *tvb, packet_info *pinfo,
                                proto_tree *tree, guint8 dch_crc_present,
                                int offset, guint header_length)
{
    int         crc_size = 0;
    int         remain   = tvb_captured_length_remaining(tvb, offset);

    /* Payload CRC (optional) */
    if ((dch_crc_present == 1) || ((dch_crc_present == 2) && (remain >= 2))) {
        crc_size = 2;
    }

    if (remain > crc_size) {
        proto_item *ti;
        ti = proto_tree_add_item(tree, hf_fp_spare_extension, tvb,
                                 offset, remain-crc_size, ENC_NA);
        proto_item_append_text(ti, " (%u octets)", remain-crc_size);
        expert_add_info_format(pinfo, ti, &ei_fp_spare_extension, "Spare Extension present (%u bytes)", remain-crc_size);
        offset += remain-crc_size;
    }

    if (crc_size) {
     proto_item * pi = proto_tree_add_item(tree, hf_fp_payload_crc, tvb, offset, crc_size,
                            ENC_BIG_ENDIAN);
        if (preferences_payload_checksum) {
            guint16 calc_crc, read_crc;
            guint8 * data = (guint8 *)tvb_memdup(wmem_packet_scope(), tvb, header_length, offset-header_length);
            calc_crc = crc16_8005_noreflect_noxor(data, offset-header_length);
            read_crc = tvb_get_bits16(tvb, offset*8, 16, ENC_BIG_ENDIAN);

            if (calc_crc == read_crc) {
                proto_item_append_text(pi, " [correct]");
            } else {
                proto_item_append_text(pi, " [incorrect, should be 0x%x]", calc_crc);
                expert_add_info(pinfo, pi, &ei_fp_bad_payload_checksum);
            }
        }
    }
}
