SpoolssGeneric_r(tvbuff_t *tvb, int offset, packet_info *pinfo,
			    proto_tree *tree, dcerpc_info *di, guint8 *drep _U_)
{
	int len = tvb_reported_length(tvb);

	proto_tree_add_expert(tree, pinfo, &ei_unimplemented_dissector, tvb, offset, 0);

	offset = dissect_doserror(
		tvb, len - 4, pinfo, tree, di, drep, hf_rc, NULL);

	return offset;
}
