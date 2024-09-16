dissect_usb_ms_bulk_heur(tvbuff_t *tvb, packet_info *pinfo, proto_tree *tree, void* data)
{
    const gchar usbc[] = {0x55, 0x53, 0x42, 0x43};
    const gchar usbs[] = {0x55, 0x53, 0x42, 0x53};
    if (tvb_reported_length(tvb) < 4)
        return FALSE;

    if (tvb_memeql(tvb, 0, usbc, sizeof(usbc)) == 0 ||
        tvb_memeql(tvb, 0, usbs, sizeof(usbs)) == 0) {
        dissect_usb_ms_bulk(tvb, pinfo, tree, data);
        return TRUE;
    }

    return FALSE;
}
