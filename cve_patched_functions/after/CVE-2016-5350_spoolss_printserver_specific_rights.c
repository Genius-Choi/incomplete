spoolss_printserver_specific_rights(tvbuff_t *tvb, gint offset,
				    proto_tree *tree, guint32 access)
{
	proto_tree_add_boolean(
		tree, hf_server_access_enum, tvb, offset, 4, access);

	proto_tree_add_boolean(
		tree, hf_server_access_admin, tvb, offset, 4, access);
}
