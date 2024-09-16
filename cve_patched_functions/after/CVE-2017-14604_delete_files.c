delete_files (CommonJob *job,
              GList     *files,
              int       *files_skipped)
{
    GList *l;
    GFile *file;
    SourceInfo source_info;
    TransferInfo transfer_info;
    DeleteData data;

    if (job_aborted (job))
    {
        return;
    }

    scan_sources (files,
                  &source_info,
                  job,
                  OP_KIND_DELETE);
    if (job_aborted (job))
    {
        return;
    }

    g_timer_start (job->time);

    memset (&transfer_info, 0, sizeof (transfer_info));
    report_delete_progress (job, &source_info, &transfer_info);

    data.job = job;
    data.source_info = &source_info;
    data.transfer_info = &transfer_info;

    for (l = files;
         l != NULL && !job_aborted (job);
         l = l->next)
    {
        gboolean success;

        file = l->data;

        if (should_skip_file (job, file))
        {
            (*files_skipped)++;
            continue;
        }

        success = delete_file_recursively (file, job->cancellable,
                                           file_deleted_callback,
                                           &data);

        if (!success)
        {
            (*files_skipped)++;
        }
    }
}
