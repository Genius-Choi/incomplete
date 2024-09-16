move_task_done (GObject      *source_object,
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
    g_object_unref (job->destination);
    g_hash_table_unref (job->debuting_files);
    g_free (job->icon_positions);

    finalize_common ((CommonJob *) job);

    nautilus_file_changes_consume_changes (TRUE);
}
