on_name_acquired(__attribute__((unused)) GDBusConnection *connection,
		 const gchar     *name,
		 __attribute__((unused)) gpointer user_data)
{
	log_message(LOG_INFO, "Acquired the name %s on the session bus", name);
}
