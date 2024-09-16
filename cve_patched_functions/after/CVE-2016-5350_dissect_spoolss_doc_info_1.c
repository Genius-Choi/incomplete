dissect_spoolss_doc_info_1(tvbuff_t *tvb, int offset, packet_info *pinfo,
			   proto_tree *tree, dcerpc_info *di, guint8 *drep)
{
	proto_tree *subtree;

	subtree = proto_tree_add_subtree(
		tree, tvb, offset, 0, ett_DOC_INFO_1, NULL, "Document info level 1");

	offset = dissect_ndr_str_pointer_item(
		tvb, offset, pinfo, subtree, di, drep, NDR_POINTER_UNIQUE,
		"Document name", hf_documentname, 0);

	offset = dissect_ndr_str_pointer_item(
		tvb, offset, pinfo, subtree, di, drep, NDR_POINTER_UNIQUE,
		"Output file", hf_outputfile, 0);

	offset = dissect_ndr_str_pointer_item(
		tvb, offset, pinfo, subtree, di, drep, NDR_POINTER_UNIQUE,
		"Data type", hf_datatype, 0);

	return offset;
}
