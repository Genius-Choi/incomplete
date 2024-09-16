register_vrrp_dbus_addresses(void)
{
	register_thread_address("handle_dbus_msg", handle_dbus_msg);
}
