dissect_usb_vid_control_info(proto_tree *tree, tvbuff_t *tvb, int offset)
{
    static const int *capability_bits[] = {
        &hf_usb_vid_control_info_D[0],
        &hf_usb_vid_control_info_D[1],
        &hf_usb_vid_control_info_D[2],
        &hf_usb_vid_control_info_D[3],
        &hf_usb_vid_control_info_D[4],
        &hf_usb_vid_control_info_D[5],
        &hf_usb_vid_control_info_D[6],
        NULL
    };

    DISSECTOR_ASSERT(array_length(capability_bits) == (1+array_length(hf_usb_vid_control_info_D)));

    proto_tree_add_bitmask(tree, tvb, offset, hf_usb_vid_control_info,
                           ett_control_capabilities, capability_bits, ENC_NA);

    return offset+1;
}
