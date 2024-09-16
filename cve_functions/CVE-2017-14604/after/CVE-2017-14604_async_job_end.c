async_job_end (NautilusDirectory *directory,
               const char        *job)
{
#ifdef DEBUG_ASYNC_JOBS
    char *key;
    gpointer table_key, value;
#endif

#ifdef DEBUG_START_STOP
    g_message ("stopping %s in %p", job, directory->details->location);
#endif

    g_assert (async_job_count > 0);

#ifdef DEBUG_ASYNC_JOBS
    {
        char *uri;
        uri = nautilus_directory_get_uri (directory);
        g_assert (async_jobs != NULL);
        key = g_strconcat (uri, ": ", job, NULL);
        if (!g_hash_table_lookup_extended (async_jobs, key, &table_key, &value))
        {
            g_warning ("ending job we didn't start: %s in %s",
                       job, uri);
        }
        else
        {
            g_hash_table_remove (async_jobs, key);
            g_free (table_key);
        }
        g_free (uri);
        g_free (key);
    }
#endif

    async_job_count -= 1;
}
