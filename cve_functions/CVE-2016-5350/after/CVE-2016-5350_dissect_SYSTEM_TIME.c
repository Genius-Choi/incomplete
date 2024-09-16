dissect_SYSTEM_TIME(tvbuff_t *tvb, int offset, packet_info *pinfo,
		    proto_tree *tree, dcerpc_info *di, guint8 *drep, const char *name,
		    gboolean add_subtree, char **data)
{
	proto_item *item = NULL;
	proto_tree *subtree = tree;
	guint16 year, month, day, hour, minute, second, millisecond;
	char *str;

	if (add_subtree) {
		subtree = proto_tree_add_subtree(tree, tvb, offset, 16, ett_SYSTEM_TIME, &item, name);
	}

	offset = dissect_ndr_uint16(
		tvb, offset, pinfo, subtree, di, drep, hf_time_year, &year);

	offset = dissect_ndr_uint16(
		tvb, offset, pinfo, subtree, di, drep, hf_time_month, &month);

	offset = dissect_ndr_uint16(
		tvb, offset, pinfo, subtree, di, drep, hf_time_dow, NULL);

	offset = dissect_ndr_uint16(
		tvb, offset, pinfo, subtree, di, drep, hf_time_day, &day);

	offset = dissect_ndr_uint16(
		tvb, offset, pinfo, subtree, di, drep, hf_time_hour, &hour);

	offset = dissect_ndr_uint16(
		tvb, offset, pinfo, subtree, di, drep, hf_time_minute, &minute);

	offset = dissect_ndr_uint16(
		tvb, offset, pinfo, subtree, di, drep, hf_time_second, &second);

	offset = dissect_ndr_uint16(
		tvb, offset, pinfo, subtree, di, drep, hf_time_msec, &millisecond);

	str = wmem_strdup_printf(wmem_packet_scope(),
			      "%d/%02d/%02d %02d:%02d:%02d.%03d",
			      year, month, day, hour, minute, second,
			      millisecond);

	if (add_subtree)
		proto_item_append_text(item, ": %s", str);

	if (data)
		*data = str;

	return offset;
}
