static bool cancel_event_run()
{
    if (g_event_child_pid <= 0)
        return false;

    kill(- g_event_child_pid, SIGTERM);
    return true;
}
