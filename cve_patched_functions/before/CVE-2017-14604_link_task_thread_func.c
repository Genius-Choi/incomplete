link_task_thread_func (GTask        *task,
                       gpointer      source_object,
                       gpointer      task_data,
                       GCancellable *cancellable)
{
    CopyMoveJob *job;
    CommonJob *common;
    GFile *src;
    GdkPoint *point;
    char *dest_fs_type;
    int total, left;
    int i;
    GList *l;

    job = task_data;
    common = &job->common;

    dest_fs_type = NULL;

    nautilus_progress_info_start (job->common.progress);

    verify_destination (&job->common,
                        job->destination,
                        NULL,
                        -1);
    if (job_aborted (common))
    {
        goto aborted;
    }

    total = left = g_list_length (job->files);

    report_preparing_link_progress (job, total, left);

    i = 0;
    for (l = job->files;
         l != NULL && !job_aborted (common);
         l = l->next)
    {
        src = l->data;

        if (i < job->n_icon_positions)
        {
            point = &job->icon_positions[i];
        }
        else
        {
            point = NULL;
        }


        link_file (job, src, job->destination,
                   &dest_fs_type, job->debuting_files,
                   point, left);
        report_preparing_link_progress (job, total, --left);
        i++;
    }

aborted:
    g_free (dest_fs_type);
}
