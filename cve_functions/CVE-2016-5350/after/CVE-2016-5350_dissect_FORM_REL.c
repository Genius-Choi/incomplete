dissect_FORM_REL(tvbuff_t *tvb, int offset, packet_info *pinfo,
			    proto_tree *tree, dcerpc_info *di, guint8 *drep, int struct_start)
{
	proto_item *item;
	proto_tree *subtree;
	guint32 flags;
	int item_start = offset;
	char *name = NULL;

	subtree = proto_tree_add_subtree(tree, tvb, offset, 0, ett_FORM_REL, &item, "Form");

	offset = dissect_ndr_uint32(
		tvb, offset, pinfo, subtree, di, drep, hf_form_flags, &flags);

	offset = dissect_spoolss_relstr(
		tvb, offset, pinfo, subtree, di, drep, hf_form_name,
		struct_start, &name);

	if (name) {
		proto_item_append_text(item, ": %s", name);
		g_free(name);
	}

	offset = dissect_ndr_uint32(
		tvb, offset, pinfo, subtree, di, drep,
		hf_form_width, NULL);

	offset = dissect_ndr_uint32(
		tvb, offset, pinfo, subtree, di, drep,
		hf_form_height, NULL);

	offset = dissect_ndr_uint32(
		tvb, offset, pinfo, subtree, di, drep,
		hf_form_left_margin, NULL);

	offset = dissect_ndr_uint32(
		tvb, offset, pinfo, subtree, di, drep,
		hf_form_top_margin, NULL);

	offset = dissect_ndr_uint32(
		tvb, offset, pinfo, subtree, di, drep,
		hf_form_horiz_len, NULL);

	offset = dissect_ndr_uint32(
		tvb, offset, pinfo, subtree, di, drep,
		hf_form_vert_len, NULL);

	proto_item_set_len(item, offset - item_start);

	return offset;
}
