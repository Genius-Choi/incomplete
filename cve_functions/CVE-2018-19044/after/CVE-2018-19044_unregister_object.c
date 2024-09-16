unregister_object(gpointer key, gpointer value, __attribute__((unused)) gpointer user_data)
{
	if (g_hash_table_remove(objects, key))
		return g_dbus_connection_unregister_object(global_connection, GPOINTER_TO_UINT(value));
	return false;
}
