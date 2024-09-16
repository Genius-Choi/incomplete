dbus_object_create_path_instance(const gchar *interface, int vrid, sa_family_t family)
{
	gchar *object_path;
	char standardized_name[sizeof ((vrrp_t*)NULL)->ifp->ifname];
	gchar *vrid_str = g_strdup_printf("%d", vrid);

	set_valid_path(standardized_name, interface);

	object_path = g_strconcat(DBUS_VRRP_OBJECT_ROOT,
#if HAVE_DECL_CLONE_NEWNET
				  global_data->network_namespace ? "/" : "", global_data->network_namespace ? global_data->network_namespace : "",
#endif
				  global_data->instance_name ? "/" : "", global_data->instance_name ? global_data->instance_name : "",

				  "/Instance/",
				  standardized_name, "/", vrid_str,
				  "/", family_str(family),
				  NULL);

	g_free(vrid_str);
	return object_path;
}
