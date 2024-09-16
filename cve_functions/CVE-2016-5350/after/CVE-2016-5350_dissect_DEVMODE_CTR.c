dissect_DEVMODE_CTR(tvbuff_t *tvb, int offset, packet_info *pinfo,
			       proto_tree *tree, dcerpc_info *di, guint8 *drep)
{
	proto_tree *subtree;
	guint32 size;

	subtree = proto_tree_add_subtree(
		tree, tvb, offset, 0, ett_DEVMODE_CTR, NULL, "Devicemode container");

	offset = dissect_ndr_uint32(tvb, offset, pinfo, subtree, di, drep,
				    hf_devmodectr_size, &size);

	offset = dissect_ndr_pointer(
		tvb, offset, pinfo, subtree, di, drep,
		dissect_DEVMODE, NDR_POINTER_UNIQUE, "Devicemode", -1);

	return offset;
}
