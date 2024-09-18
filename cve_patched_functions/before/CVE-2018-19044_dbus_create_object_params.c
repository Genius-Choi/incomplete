dbus_create_object_params(char *instance_name, const char *interface_name, int vrid, sa_family_t family, bool log_success)
{
	gchar *object_path;
	GError *local_error = NULL;

	if (g_hash_table_lookup(objects, instance_name)) {
		log_message(LOG_INFO, "An object for instance %s already exists", instance_name);
		return DBUS_OBJECT_ALREADY_EXISTS;
	}

	object_path = dbus_object_create_path_instance(interface_name, vrid, family);

	guint instance = g_dbus_connection_register_object(global_connection, object_path,
						vrrp_instance_introspection_data->interfaces[0],
						&interface_vtable, NULL, NULL, &local_error);
	if (local_error != NULL) {
		log_message(LOG_INFO, "Registering DBus object on %s failed: %s",
			    object_path, local_error->message);
		g_clear_error(&local_error);
	}

	if (instance) {
		g_hash_table_insert(objects, instance_name, GUINT_TO_POINTER(instance));
		if (log_success)
			log_message(LOG_INFO, "Added DBus object for instance %s on path %s", instance_name, object_path);
	}
	g_free(object_path);

	return DBUS_SUCCESS;
}
