dissect_ac_if_input_terminal(tvbuff_t *tvb, gint offset, packet_info *pinfo _U_,
        proto_tree *tree, usb_conv_info_t *usb_conv_info _U_)
{
    gint     offset_start;
    offset_start = offset;

    proto_tree_add_item(tree, hf_ac_if_input_terminalid, tvb, offset, 1, ENC_LITTLE_ENDIAN);
    offset += 1;

    proto_tree_add_item(tree, hf_ac_if_input_terminaltype, tvb, offset, 2, ENC_LITTLE_ENDIAN);
    offset += 2;

    proto_tree_add_item(tree, hf_ac_if_input_assocterminal, tvb, offset, 1, ENC_LITTLE_ENDIAN);
    offset += 1;

    proto_tree_add_item(tree, hf_ac_if_input_nrchannels, tvb, offset, 1, ENC_LITTLE_ENDIAN);
    offset += 1;

    proto_tree_add_item(tree, hf_ac_if_input_channelconfig, tvb, offset, 2, ENC_LITTLE_ENDIAN);
    offset += 2;

    proto_tree_add_item(tree, hf_ac_if_input_channelnames, tvb, offset, 1, ENC_LITTLE_ENDIAN);
    offset += 1;

    proto_tree_add_item(tree, hf_ac_if_input_terminal, tvb, offset, 1, ENC_LITTLE_ENDIAN);
    offset += 1;

    return offset-offset_start;
}
