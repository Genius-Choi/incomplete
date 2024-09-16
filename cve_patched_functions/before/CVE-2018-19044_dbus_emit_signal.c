dbus_emit_signal(GDBusConnection *connection,
		 const gchar *object_path,
		 const gchar *interface_name,
		 const gchar *signal_name,
		 GVariant *parameters)
{
	GError *local_error = NULL;

	g_dbus_connection_emit_signal(connection, NULL, object_path, interface_name, signal_name, parameters,
				      &local_error);

	if (local_error != NULL) {
		log_message(LOG_INFO, "Emitting DBus signal %s.%s on %s failed: %s",
			    interface_name, signal_name, object_path, local_error->message);
		g_clear_error(&local_error);
		return false;
	}
	return true;
}
