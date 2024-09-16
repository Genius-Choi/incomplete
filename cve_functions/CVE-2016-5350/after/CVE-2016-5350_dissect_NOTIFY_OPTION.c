dissect_NOTIFY_OPTION(tvbuff_t *tvb, int offset, packet_info *pinfo,
		      proto_tree *tree, dcerpc_info *di, guint8 *drep)
{
	dcerpc_call_value *dcv = (dcerpc_call_value *)di->call_data;
	proto_item *item;
	proto_tree *subtree;
	guint16 type;
	guint32 count;

	subtree = proto_tree_add_subtree(tree, tvb, offset, 0, ett_NOTIFY_OPTION, &item, "Notify Option");

	offset = dissect_ndr_uint16(tvb, offset, pinfo, subtree, di, drep,
				    hf_notify_option_type, &type);

	proto_item_append_text(
		item, ": %s", val_to_str(type, printer_notify_types,
					 "Unknown (%d)"));

	offset = dissect_ndr_uint16(tvb, offset, pinfo, subtree, di, drep,
				    hf_notify_option_reserved1, NULL);

	offset = dissect_ndr_uint32(tvb, offset, pinfo, subtree, di, drep,
				    hf_notify_option_reserved2, NULL);

	offset = dissect_ndr_uint32(tvb, offset, pinfo, subtree, di, drep,
				    hf_notify_option_reserved3, NULL);

	offset = dissect_ndr_uint32(tvb, offset, pinfo, subtree, di, drep,
				    hf_notify_option_count, &count);

	proto_item_append_text(
		item, ", %d %s", count, notify_plural(count));

	dcv->private_data = GINT_TO_POINTER((int)type);

	offset = dissect_ndr_pointer(
		tvb, offset, pinfo, subtree, di, drep,
		dissect_NOTIFY_OPTION_DATA, NDR_POINTER_UNIQUE,
		"Notify Option Data", -1);

	return offset;
}
