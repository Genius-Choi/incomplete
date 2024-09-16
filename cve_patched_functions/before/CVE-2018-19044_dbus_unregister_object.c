dbus_unregister_object(char *str)
{
	gboolean ret = false;

	gpointer value = g_hash_table_lookup(objects, str);
	if (value) {
		ret = unregister_object(str, value, NULL);
		log_message(LOG_INFO, "Deleted DBus object for instance %s", str);
	}
#ifdef DBUS_DEBUG
	else
		log_message(LOG_INFO, "DBus object not found for instance %s", str);
#endif

	return ret;
}
