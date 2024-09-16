dissect_printerdata_data(tvbuff_t *tvb, int offset,
				    packet_info *pinfo, proto_tree *tree,
				    dcerpc_info *di, guint8 *drep _U_, guint32 type)
{
	proto_item *item, *hidden_item;
	proto_tree *subtree;
	guint32 size;

	subtree = proto_tree_add_subtree(tree, tvb, offset, 0, ett_printerdata_data, &item, "Data");

	offset = dissect_ndr_uint32(
		tvb, offset, pinfo, subtree, di, drep, hf_printerdata_size, &size);

	if (size) {

		offset = dissect_ndr_uint8s(
			tvb, offset, pinfo, subtree, di, drep,
			hf_printerdata_data, size, NULL);

		switch(type) {
		case DCERPC_REG_SZ: {
			char *data = tvb_get_string_enc(NULL, tvb, offset - size, size, ENC_UTF_16|ENC_LITTLE_ENDIAN);

			proto_item_append_text(item, ": %s", data);

			col_append_fstr(
					pinfo->cinfo, COL_INFO, " = %s", data);

			hidden_item = proto_tree_add_string(
				tree, hf_printerdata_data_sz, tvb,
				offset - size, size, data);
			PROTO_ITEM_SET_HIDDEN(hidden_item);

			g_free(data);

			break;
		}
		case DCERPC_REG_DWORD: {
			guint32 data = tvb_get_letohl(tvb, offset - size);

			proto_item_append_text(item, ": 0x%08x", data);

			col_append_fstr(
					pinfo->cinfo, COL_INFO, " = 0x%08x",
					data);

			hidden_item = proto_tree_add_uint(
				tree, hf_printerdata_data_dword, tvb,
				offset - size, 4, data);
			PROTO_ITEM_SET_HIDDEN(hidden_item);

			break;
		}
		case DCERPC_REG_BINARY:
			col_append_str(
					pinfo->cinfo, COL_INFO,
					" = <binary data>");
			break;

		default:
			break;
		}
	}

	proto_item_set_len(item, size + 4);

	return offset;
}
