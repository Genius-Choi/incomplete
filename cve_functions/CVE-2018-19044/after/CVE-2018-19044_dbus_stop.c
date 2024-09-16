dbus_stop(void)
{
	struct timespec thread_end_wait;
	int ret;
	gchar *path;

	if (global_connection != NULL) {
		path = dbus_object_create_path_vrrp();
		dbus_emit_signal(global_connection, path, DBUS_VRRP_INTERFACE, "VrrpStopped", NULL);
		g_free(path);
	}

	g_main_loop_quit(loop);

	g_dbus_node_info_unref(vrrp_introspection_data);
	g_dbus_node_info_unref(vrrp_instance_introspection_data);

	clock_gettime(CLOCK_REALTIME, &thread_end_wait);
	thread_end_wait.tv_sec += 1;
	while ((ret = sem_timedwait(&thread_end, &thread_end_wait)) == -1 && errno == EINTR) ;

	if (ret == -1 ) {
		if (errno == ETIMEDOUT)
			log_message(LOG_INFO, "DBus thread termination timed out");
		else
			log_message(LOG_INFO, "sem_timewait error %d", errno);
	}
	else {
		log_message(LOG_INFO, "Released DBus");
		sem_destroy(&thread_end);
	}
}
