async_job_wake_up (void)
{
    static gboolean already_waking_up = FALSE;
    gpointer value;

    g_assert (async_job_count >= 0);
    g_assert (async_job_count <= MAX_ASYNC_JOBS);

    if (already_waking_up)
    {
        return;
    }

    already_waking_up = TRUE;
    while (async_job_count < MAX_ASYNC_JOBS)
    {
        value = get_one_value (waiting_directories);
        if (value == NULL)
        {
            break;
        }
        g_hash_table_remove (waiting_directories, value);
        nautilus_directory_async_state_changed
            (NAUTILUS_DIRECTORY (value));
    }
    already_waking_up = FALSE;
}
