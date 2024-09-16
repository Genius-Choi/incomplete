dissect_DRIVER_INFO_101(tvbuff_t *tvb, int offset,
				 packet_info *pinfo, proto_tree *tree,
				 dcerpc_info *di, guint8 *drep)
{
	proto_tree *subtree;
	int struct_start = offset;

	subtree = proto_tree_add_subtree(
			tree, tvb, offset, 0, ett_DRIVER_INFO_101, NULL, "Driver info level 101");

	offset = dissect_ndr_uint32(tvb, offset, pinfo, subtree, di, drep,
			hf_driverinfo_cversion, NULL);

	offset = dissect_spoolss_relstr(
			tvb, offset, pinfo, subtree, di, drep, hf_drivername,
			struct_start, NULL);

	offset = dissect_spoolss_relstr(
			tvb, offset, pinfo, subtree, di, drep, hf_environment,
			struct_start, NULL);

	proto_tree_add_expert(subtree, pinfo, &ei_unknown_data, tvb, offset, 0);

	return offset;
}
