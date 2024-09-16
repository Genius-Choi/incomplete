dissect_NOTIFY_OPTION_DATA(tvbuff_t *tvb, int offset, packet_info *pinfo,
			   proto_tree *tree, dcerpc_info *di, guint8 *drep)
{
	dcerpc_call_value *dcv = (dcerpc_call_value *)di->call_data;
	guint32 count, i;
	guint16 type;

	if (di->conformant_run)
		return offset;

	offset = dissect_ndr_uint32(
		tvb, offset, pinfo, tree, di, drep,
		hf_notify_option_data_count, &count);

	type = GPOINTER_TO_INT(dcv->private_data);

	for (i = 0; i < count; i++)
		offset = dissect_notify_field(
			tvb, offset, pinfo, tree, di, drep, type, NULL);

	return offset;
}
