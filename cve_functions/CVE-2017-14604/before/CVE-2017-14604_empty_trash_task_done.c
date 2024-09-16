empty_trash_task_done (GObject      *source_object,
                       GAsyncResult *res,
                       gpointer      user_data)
{
    EmptyTrashJob *job;

    job = user_data;

    g_list_free_full (job->trash_dirs, g_object_unref);

    if (job->done_callback)
    {
        job->done_callback (!job_aborted ((CommonJob *) job),
                            job->done_callback_data);
    }

    finalize_common ((CommonJob *) job);
}
