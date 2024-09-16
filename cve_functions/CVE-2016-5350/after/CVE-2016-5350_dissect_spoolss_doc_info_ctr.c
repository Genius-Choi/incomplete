dissect_spoolss_doc_info_ctr(tvbuff_t *tvb, int offset, packet_info *pinfo,
			     proto_tree *tree, dcerpc_info *di, guint8 *drep)
{
	proto_tree *subtree;

	subtree = proto_tree_add_subtree(
		tree, tvb, offset, 0, ett_DOC_INFO_CTR, NULL, "Document info container");

	offset = dissect_ndr_uint32(
		tvb, offset, pinfo, subtree, di, drep, hf_level, NULL);

	offset = dissect_spoolss_doc_info(
		tvb, offset, pinfo, subtree, di, drep);

	return offset;
}
