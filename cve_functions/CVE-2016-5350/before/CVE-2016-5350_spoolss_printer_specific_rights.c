spoolss_printer_specific_rights(tvbuff_t *tvb, gint offset, proto_tree *tree,
				guint32 access)
{
	proto_tree_add_boolean(
		tree, hf_printer_access_use, tvb, offset, 4, access);

	proto_tree_add_boolean(
		tree, hf_printer_access_admin, tvb, offset, 4, access);
}
