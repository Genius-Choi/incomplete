dissect_usb_video_colorformat(proto_tree *tree, tvbuff_t *tvb, int offset)
{
    proto_tree_add_item(tree, hf_usb_vid_color_primaries,          tvb, offset,   1, ENC_LITTLE_ENDIAN);
    proto_tree_add_item(tree, hf_usb_vid_transfer_characteristics, tvb, offset+1, 1, ENC_LITTLE_ENDIAN);
    proto_tree_add_item(tree, hf_usb_vid_matrix_coefficients,      tvb, offset+2, 1, ENC_LITTLE_ENDIAN);
    offset +=3;

    return offset;
}
