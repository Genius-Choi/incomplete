static void cgm_dbus_disconnect(void)
{
	if (cgroup_manager) {
		dbus_connection_flush(cgroup_manager->connection);
		dbus_connection_close(cgroup_manager->connection);
		nih_free(cgroup_manager);
	}
	cgroup_manager = NULL;
	cgm_unlock();
}
