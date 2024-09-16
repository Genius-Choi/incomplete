dbus_service_name_handler(vector_t *strvec)
{
	FREE_PTR(global_data->dbus_service_name);
	global_data->dbus_service_name = set_value(strvec);
}
