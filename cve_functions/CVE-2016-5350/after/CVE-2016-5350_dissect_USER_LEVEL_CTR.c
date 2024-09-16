dissect_USER_LEVEL_CTR(tvbuff_t *tvb, int offset,
				  packet_info *pinfo, proto_tree *tree,
				  dcerpc_info *di, guint8 *drep)
{
	proto_tree *subtree;
	proto_item *item;
	guint32 level;

	if (di->conformant_run)
		return offset;

	subtree = proto_tree_add_subtree(
		tree, tvb, offset, 0, ett_USER_LEVEL_CTR, &item, "User level container");

	offset = dissect_ndr_uint32(
		tvb, offset, pinfo, subtree, di, drep, hf_level, &level);

	switch(level) {
	case 1:
		offset = dissect_ndr_pointer(
			tvb, offset, pinfo, subtree, di, drep,
			dissect_USER_LEVEL_1, NDR_POINTER_UNIQUE,
			"User level 1", -1);
		break;
	default:
		expert_add_info_format(pinfo, item, &ei_level, "Info level %d not decoded", level);
		break;
	}

	return offset;
}
