dissect_printer_attributes(tvbuff_t *tvb, int offset, packet_info *pinfo,
			   proto_tree *tree, dcerpc_info *di, guint8 *drep)
{
	guint32 attributes;
	static const int * hf_attributes[] = {
		&hf_printer_attributes_published,
		&hf_printer_attributes_raw_only,
		&hf_printer_attributes_enable_bidi,
		&hf_printer_attributes_work_offline,
		&hf_printer_attributes_do_complete_first,
		&hf_printer_attributes_keep_printed_jobs,
		&hf_printer_attributes_enable_devq,
		&hf_printer_attributes_local,
		&hf_printer_attributes_hidden,
		&hf_printer_attributes_network,
		&hf_printer_attributes_shared,
		&hf_printer_attributes_default,
		&hf_printer_attributes_direct,
		&hf_printer_attributes_queued,
		NULL
	};

	offset = dissect_ndr_uint32(tvb, offset, pinfo, NULL, di, drep, -1, &attributes);

	proto_tree_add_bitmask_value_with_flags(tree, tvb, offset - 4, hf_printer_attributes,
					ett_printer_attributes, hf_attributes, attributes, BMT_NO_APPEND);

	return offset;
}
