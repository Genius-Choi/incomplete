dbus_send_reload_signal(void)
{
	gchar *path;

	if (global_connection == NULL)
		return;

	path = dbus_object_create_path_vrrp();
	dbus_emit_signal(global_connection, path, DBUS_VRRP_INTERFACE, "VrrpReloaded", NULL);
	g_free(path);
}
