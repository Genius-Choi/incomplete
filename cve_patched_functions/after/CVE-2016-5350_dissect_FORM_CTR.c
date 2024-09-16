dissect_FORM_CTR(tvbuff_t *tvb, int offset,
			    packet_info *pinfo, proto_tree *tree,
			    dcerpc_info *di, guint8 *drep)
{
	proto_tree *subtree;
	proto_item *item;
	guint32 level;

	subtree = proto_tree_add_subtree(tree, tvb, offset, 0, ett_FORM_CTR, &item, "Form container");

	offset = dissect_ndr_uint32(
		tvb, offset, pinfo, subtree, di, drep, hf_form_level, &level);

	switch(level) {
	case 1:
		offset = dissect_FORM_1(tvb, offset, pinfo, subtree, di, drep);
		break;

	default:
		expert_add_info_format(pinfo, item, &ei_form_level, "Unknown form info level %d", level);
		break;
	}

	return offset;
}
