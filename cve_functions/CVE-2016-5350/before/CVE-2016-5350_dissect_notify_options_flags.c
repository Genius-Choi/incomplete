dissect_notify_options_flags(tvbuff_t *tvb, int offset, packet_info *pinfo,
			     proto_tree *tree, dcerpc_info *di, guint8 *drep)
{
	guint32 flags;
	static const int * hf_flags[] = {
		&hf_notify_options_flags_refresh,
		NULL
	};

	offset = dissect_ndr_uint32(tvb, offset, pinfo, NULL, di, drep, -1, &flags);

	proto_tree_add_bitmask_value_with_flags(tree, tvb, offset - 4, hf_notify_options_flags,
					ett_notify_options_flags, hf_flags, flags, BMT_NO_APPEND);

	return offset;
}
