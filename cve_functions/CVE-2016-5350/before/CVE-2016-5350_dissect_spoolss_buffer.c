dissect_spoolss_buffer(tvbuff_t *tvb, gint offset, packet_info *pinfo,
		       proto_tree *tree, dcerpc_info *di, guint8 *drep, BUFFER *b)
{
	if (b)
		memset(b, 0, sizeof(BUFFER));

	di->private_data = b;

	offset = dissect_ndr_pointer(
		tvb, offset, pinfo, tree, di, drep,
		dissect_spoolss_buffer_data, NDR_POINTER_UNIQUE,
		"Buffer", -1);

	return offset;
}
