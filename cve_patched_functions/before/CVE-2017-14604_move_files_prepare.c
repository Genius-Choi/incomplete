move_files_prepare (CopyMoveJob  *job,
                    const char   *dest_fs_id,
                    char        **dest_fs_type,
                    GList       **fallbacks)
{
    CommonJob *common;
    GList *l;
    GFile *src;
    gboolean same_fs;
    int i;
    GdkPoint *point;
    int total, left;

    common = &job->common;

    total = left = g_list_length (job->files);

    report_preparing_move_progress (job, total, left);

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


        same_fs = FALSE;
        if (dest_fs_id)
        {
            same_fs = has_fs_id (src, dest_fs_id);
        }

        move_file_prepare (job, src, job->destination,
                           same_fs, dest_fs_type,
                           job->debuting_files,
                           point,
                           fallbacks,
                           left);
        report_preparing_move_progress (job, total, --left);
        i++;
    }

    *fallbacks = g_list_reverse (*fallbacks);
}
