dissect_PRINTER_DATATYPE(tvbuff_t *tvb, int offset,
				    packet_info *pinfo, proto_tree *tree,
				    dcerpc_info *di, guint8 *drep _U_)
{
	if (di->conformant_run)
		return offset;

	offset = dissect_ndr_cvstring(
		tvb, offset, pinfo, tree, di, drep, sizeof(guint16),
		hf_datatype, TRUE, NULL);

	return offset;
}
