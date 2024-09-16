dissect_NOTIFY_OPTIONS_ARRAY_CTR(tvbuff_t *tvb, int offset,
				 packet_info *pinfo, proto_tree *tree,
				 dcerpc_info *di, guint8 *drep)
{
	if (di->conformant_run)
		return offset;

	offset = dissect_ndr_uint32(tvb, offset, pinfo, tree, di, drep,
				    hf_notify_options_version, NULL);

	offset = dissect_notify_options_flags(tvb, offset, pinfo, tree, di, drep);

	offset = dissect_ndr_uint32(tvb, offset, pinfo, tree, di, drep,
				    hf_notify_options_count, NULL);

	offset = dissect_ndr_pointer(
		tvb, offset, pinfo, tree, di, drep,
		dissect_NOTIFY_OPTIONS_ARRAY, NDR_POINTER_UNIQUE,
		"Notify Options Array", -1);

	return offset;
}
