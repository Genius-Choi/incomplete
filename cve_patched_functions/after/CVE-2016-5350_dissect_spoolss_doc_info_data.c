dissect_spoolss_doc_info_data(tvbuff_t *tvb, int offset, packet_info *pinfo,
			      proto_tree *tree, dcerpc_info *di, guint8 *drep)
{
	if (di->conformant_run)
		return offset;

	return dissect_spoolss_doc_info_1(tvb, offset, pinfo, tree, di, drep);
}
