dissect_spoolss_doc_info(tvbuff_t *tvb, int offset, packet_info *pinfo,
			 proto_tree *tree, dcerpc_info *di, guint8 *drep)
{
	proto_tree *subtree;
	guint32 level;

	subtree = proto_tree_add_subtree(
		tree, tvb, offset, 0, ett_DOC_INFO, NULL, "Document info");

	offset = dissect_ndr_uint32(
		tvb, offset, pinfo, subtree, di, drep, hf_level, &level);

	offset = dissect_ndr_pointer(
		tvb, offset, pinfo, subtree, di, drep,
		dissect_spoolss_doc_info_data,
		NDR_POINTER_UNIQUE, "Document info", -1);

	return offset;
}
