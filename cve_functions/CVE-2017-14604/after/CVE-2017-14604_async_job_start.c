async_job_start (NautilusDirectory *directory,
                 const char        *job)
{
#ifdef DEBUG_ASYNC_JOBS
    char *key;
#endif

#ifdef DEBUG_START_STOP
    g_message ("starting %s in %p", job, directory->details->location);
#endif

    g_assert (async_job_count >= 0);
    g_assert (async_job_count <= MAX_ASYNC_JOBS);

    if (async_job_count >= MAX_ASYNC_JOBS)
    {
        if (waiting_directories == NULL)
        {
            waiting_directories = g_hash_table_new (NULL, NULL);
        }

        g_hash_table_insert (waiting_directories,
                             directory,
                             directory);

        return FALSE;
    }

#ifdef DEBUG_ASYNC_JOBS
    {
        char *uri;
        if (async_jobs == NULL)
        {
            async_jobs = g_hash_table_new (g_str_hash, g_str_equal);
        }
        uri = nautilus_directory_get_uri (directory);
        key = g_strconcat (uri, ": ", job, NULL);
        if (g_hash_table_lookup (async_jobs, key) != NULL)
        {
            g_warning ("same job twice: %s in %s",
                       job, uri);
        }
        g_free (uri);
        g_hash_table_insert (async_jobs, key, directory);
    }
#endif

    async_job_count += 1;
    return TRUE;
}
