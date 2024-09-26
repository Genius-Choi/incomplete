mon_cib_connection_destroy(gpointer user_data)
{
    print_as("Connection to the CIB terminated\n");
    if (cib) {
        print_as("Reconnecting...");
        cib->cmds->signoff(cib);
        timer_id = g_timeout_add(reconnect_msec, mon_timer_popped, NULL);
    }
    return;
}
