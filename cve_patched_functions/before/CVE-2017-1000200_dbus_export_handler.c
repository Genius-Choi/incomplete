dbus_export_handler(struct tcmur_handler *handler, GCallback check_config)
{
	GDBusObjectSkeleton *object;
	char obj_name[128];
	TCMUService1 *interface;

	snprintf(obj_name, sizeof(obj_name), "/org/kernel/TCMUService1/%s",
		 handler->subtype);
	object = g_dbus_object_skeleton_new(obj_name);
	interface = tcmuservice1_skeleton_new();
	g_dbus_object_skeleton_add_interface(object, G_DBUS_INTERFACE_SKELETON(interface));
	g_signal_connect(interface,
			 "handle-check-config",
			 check_config,
			 handler); /* user_data */
	tcmuservice1_set_config_desc(interface, handler->cfg_desc);
	g_dbus_object_manager_server_export(manager, G_DBUS_OBJECT_SKELETON(object));
	g_object_unref(object);
}
