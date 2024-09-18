static bool lxc_list_controllers(char ***list)
{
	if (!cgm_dbus_connect()) {
		ERROR("Error connecting to cgroup manager");
		return false;
	}
	if (cgmanager_list_controllers_sync(NULL, cgroup_manager, list) != 0) {
		NihError *nerr;
		nerr = nih_error_get();
		ERROR("call to cgmanager_list_controllers_sync failed: %s", nerr->message);
		nih_free(nerr);
		cgm_dbus_disconnect();
		return false;
	}

	cgm_dbus_disconnect();
	return true;
}
