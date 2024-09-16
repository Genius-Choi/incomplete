dissect_ac_if_feature_unit(tvbuff_t *tvb, gint offset, packet_info *pinfo _U_,
        proto_tree *tree, usb_conv_info_t *usb_conv_info _U_)
{
    gint     offset_start;
    guint8 controlsize;
    proto_tree *bitmap_tree;
    proto_item *ti;

    static const int *fu_controls0[] = {
        &hf_ac_if_fu_controls_d0,
        &hf_ac_if_fu_controls_d1,
        &hf_ac_if_fu_controls_d2,
        &hf_ac_if_fu_controls_d3,
        &hf_ac_if_fu_controls_d4,
        &hf_ac_if_fu_controls_d5,
        &hf_ac_if_fu_controls_d6,
        &hf_ac_if_fu_controls_d7,
        NULL };

    static const int *fu_controls1[] = {
        &hf_ac_if_fu_controls_d8,
        &hf_ac_if_fu_controls_d9,
        &hf_ac_if_fu_controls_rsv,
        NULL };

    offset_start = offset;

    proto_tree_add_item(tree, hf_ac_if_fu_unitid, tvb, offset, 1, ENC_LITTLE_ENDIAN);
    offset += 1;

    proto_tree_add_item(tree, hf_ac_if_fu_sourceid, tvb, offset, 1, ENC_LITTLE_ENDIAN);
    offset += 1;

    proto_tree_add_item(tree, hf_ac_if_fu_controlsize, tvb, offset, 1, ENC_LITTLE_ENDIAN);
    controlsize = tvb_get_guint8(tvb, offset) + 1;
    offset += 1;

    ti = proto_tree_add_item(tree, hf_ac_if_fu_controls, tvb, offset, controlsize, ENC_NA);
    bitmap_tree = proto_item_add_subtree(ti, ett_ac_if_fu_controls);

    proto_tree_add_bitmask(bitmap_tree, tvb, offset, hf_ac_if_fu_control, ett_ac_if_fu_controls0, fu_controls0, ENC_LITTLE_ENDIAN);

    if(controlsize >= 1){
        proto_tree_add_bitmask(bitmap_tree, tvb, offset + 1, hf_ac_if_fu_control, ett_ac_if_fu_controls1, fu_controls1, ENC_LITTLE_ENDIAN);
    }

    offset += controlsize;

    proto_tree_add_item(tree, hf_ac_if_fu_ifeature, tvb, offset, 1, ENC_LITTLE_ENDIAN);
    offset += 1;

    return offset-offset_start;
}
