copy_task_done (GObject      *source_object,
                GAsyncResult *res,
                gpointer      user_data)
{
    CopyMoveJob *job;

    job = user_data;
    if (job->done_callback)
    {
        job->done_callback (job->debuting_files,
                            !job_aborted ((CommonJob *) job),
                            job->done_callback_data);
    }

    g_list_free_full (job->files, g_object_unref);
    if (job->destination)
    {
        g_object_unref (job->destination);
    }
    if (job->desktop_location)
    {
        g_object_unref (job->desktop_location);
    }
    g_hash_table_unref (job->debuting_files);
    g_free (job->icon_positions);
    g_free (job->target_name);

    g_clear_object (&job->fake_display_source);

    finalize_common ((CommonJob *) job);

    nautilus_file_changes_consume_changes (TRUE);
}
