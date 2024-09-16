dissect_spoolss_string_parm(tvbuff_t *tvb, gint offset, packet_info *pinfo,
		       proto_tree *tree, dcerpc_info *di, guint8 *drep, const char *text)
{
	offset = dissect_ndr_pointer(
		tvb, offset, pinfo, tree, di, drep,
		dissect_spoolss_string_parm_data, NDR_POINTER_UNIQUE,
		text, -1);

	return offset;
}
