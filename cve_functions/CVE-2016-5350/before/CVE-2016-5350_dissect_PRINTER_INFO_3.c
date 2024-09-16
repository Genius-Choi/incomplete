dissect_PRINTER_INFO_3(tvbuff_t *tvb, int offset,
				  packet_info *pinfo, proto_tree *tree,
				  dcerpc_info *di, guint8 *drep)
{
	offset = dissect_ndr_uint32(
		tvb, offset, pinfo, tree, di, drep,
		hf_printer_flags, NULL);

	offset = dissect_nt_sec_desc(
		tvb, offset, pinfo, tree, drep,
		FALSE, -1,
		&spoolss_printer_access_mask_info);

	return offset;
}
