mon_timer_popped(gpointer data)
{
    int rc = pcmk_ok;

    if (timer_id > 0) {
        g_source_remove(timer_id);
    }

    rc = cib_connect(TRUE);

    if (rc != pcmk_ok) {
        print_dot();
        timer_id = g_timeout_add(reconnect_msec, mon_timer_popped, NULL);
    }
    return FALSE;
}
