dissect_bmControl(proto_tree *tree, tvbuff_t *tvb, int offset,
                  gint ett_subtree, const int** bm_items)
{
    guint8 bm_size = 0;

    bm_size = tvb_get_guint8(tvb, offset);
    proto_tree_add_item(tree, hf_usb_vid_bControlSize, tvb, offset, 1, ENC_LITTLE_ENDIAN);
    ++offset;

    if (bm_size > 0)
    {
        proto_tree_add_bitmask_len(tree, tvb, offset, bm_size, hf_usb_vid_bmControl,
                                   ett_subtree, bm_items, &ei_usb_vid_bitmask_len, ENC_LITTLE_ENDIAN);
        offset += bm_size;
    }

    return offset;
}
