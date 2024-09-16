trash_files (CommonJob *job,
             GList     *files,
             int       *files_skipped)
{
    GList *l;
    GFile *file;
    GList *to_delete;
    SourceInfo source_info;
    TransferInfo transfer_info;
    gboolean skipped_file;

    if (job_aborted (job))
    {
        return;
    }

    scan_sources (files,
                  &source_info,
                  job,
                  OP_KIND_TRASH);
    if (job_aborted (job))
    {
        return;
    }

    g_timer_start (job->time);

    memset (&transfer_info, 0, sizeof (transfer_info));
    report_trash_progress (job, &source_info, &transfer_info);

    to_delete = NULL;
    for (l = files;
         l != NULL && !job_aborted (job);
         l = l->next)
    {
        file = l->data;

        skipped_file = FALSE;
        trash_file (job, file,
                    &skipped_file,
                    &source_info, &transfer_info,
                    TRUE, &to_delete);
        if (skipped_file)
        {
            (*files_skipped)++;
            transfer_add_file_to_count (file, job, &transfer_info);
            report_trash_progress (job, &source_info, &transfer_info);
        }
    }

    if (to_delete)
    {
        to_delete = g_list_reverse (to_delete);
        delete_files (job, to_delete, files_skipped);
        g_list_free (to_delete);
    }
}
