extract_task_done (GObject      *source_object,
                   GAsyncResult *res,
                   gpointer      user_data)
{
    ExtractJob *extract_job;

    extract_job = user_data;

    if (extract_job->done_callback)
    {
        extract_job->done_callback (extract_job->output_files,
                                    extract_job->done_callback_data);
    }

    g_list_free_full (extract_job->source_files, g_object_unref);
    g_list_free_full (extract_job->output_files, g_object_unref);
    g_object_unref (extract_job->destination_directory);

    finalize_common ((CommonJob *) extract_job);

    nautilus_file_changes_consume_changes (TRUE);
}
