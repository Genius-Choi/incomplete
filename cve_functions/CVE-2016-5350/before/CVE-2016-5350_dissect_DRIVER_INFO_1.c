dissect_DRIVER_INFO_1(tvbuff_t *tvb, int offset,
				 packet_info *pinfo, proto_tree *tree,
				 dcerpc_info *di, guint8 *drep)
{
	proto_tree *subtree;
	int struct_start = offset;

	subtree = proto_tree_add_subtree(
		tree, tvb, offset, 0, ett_DRIVER_INFO_1, NULL, "Driver info level 1");

	offset = dissect_spoolss_relstr(
		tvb, offset, pinfo, subtree, di, drep, hf_drivername,
		struct_start, NULL);

	return offset;
}
