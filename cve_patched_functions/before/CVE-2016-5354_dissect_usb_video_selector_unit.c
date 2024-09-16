dissect_usb_video_selector_unit(proto_tree *tree, tvbuff_t *tvb, int offset)
{
    guint8 num_inputs;

    num_inputs = tvb_get_guint8(tvb, offset);
    proto_tree_add_item(tree, hf_usb_vid_num_inputs, tvb, offset, 1, ENC_LITTLE_ENDIAN);
    ++offset;

    if (num_inputs > 0)
    {
        proto_tree_add_item(tree, hf_usb_vid_sources, tvb, offset, num_inputs, ENC_NA);
        offset += num_inputs;
    }

    proto_tree_add_item(tree, hf_usb_vid_iSelector, tvb, offset, 1, ENC_LITTLE_ENDIAN);
    ++offset;

    return offset;
}
