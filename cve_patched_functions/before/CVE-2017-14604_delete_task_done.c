delete_task_done (GObject      *source_object,
                  GAsyncResult *res,
                  gpointer      user_data)
{
    DeleteJob *job;
    GHashTable *debuting_uris;

    job = user_data;

    g_list_free_full (job->files, g_object_unref);

    if (job->done_callback)
    {
        debuting_uris = g_hash_table_new_full (g_file_hash, (GEqualFunc) g_file_equal, g_object_unref, NULL);
        job->done_callback (debuting_uris, job->user_cancel, job->done_callback_data);
        g_hash_table_unref (debuting_uris);
    }

    finalize_common ((CommonJob *) job);

    nautilus_file_changes_consume_changes (TRUE);
}
