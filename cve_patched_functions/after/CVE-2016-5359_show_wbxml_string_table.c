show_wbxml_string_table (proto_tree *tree, tvbuff_t *tvb, guint32 str_tbl,
			 guint32 str_tbl_len)
{
	guint32 off = str_tbl;
	guint32 len = 0;
	guint32 end = str_tbl + str_tbl_len;

	proto_tree_add_text (tree, tvb, off, end,
			     "Start  | Length | String");
	while (off < end) {
		len = tvb_strsize (tvb, off);
		proto_tree_add_text (tree, tvb, off, len,
				     "%6d | %6d | '%s'",
				     off - str_tbl, len,
				     tvb_format_text (tvb, off, len-1));
		off += len;
	}
}
