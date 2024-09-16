compress_task_done (GObject      *source_object,
                    GAsyncResult *res,
                    gpointer      user_data)
{
    CompressJob *compress_job = user_data;

    if (compress_job->done_callback)
    {
        compress_job->done_callback (compress_job->output_file,
                                     compress_job->success,
                                     compress_job->done_callback_data);
    }

    g_object_unref (compress_job->output_file);
    g_list_free_full (compress_job->source_files, g_object_unref);

    finalize_common ((CommonJob *) compress_job);

    nautilus_file_changes_consume_changes (TRUE);
}
