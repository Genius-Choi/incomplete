on_name_lost(GDBusConnection *connection,
	     const gchar     *name,
	     __attribute__((unused)) gpointer user_data)
{
	log_message(LOG_INFO, "Lost the name %s on the session bus", name);
	global_connection = connection;
	g_hash_table_foreach_remove(objects, unregister_object, NULL);
	objects = NULL;
	global_connection = NULL;
}
