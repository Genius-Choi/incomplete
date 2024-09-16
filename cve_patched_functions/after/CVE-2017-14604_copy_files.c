copy_files (CopyMoveJob  *job,
            const char   *dest_fs_id,
            SourceInfo   *source_info,
            TransferInfo *transfer_info)
{
    CommonJob *common;
    GList *l;
    GFile *src;
    gboolean same_fs;
    int i;
    GdkPoint *point;
    gboolean skipped_file;
    gboolean unique_names;
    GFile *dest;
    GFile *source_dir;
    char *dest_fs_type;
    GFileInfo *inf;
    gboolean readonly_source_fs;

    dest_fs_type = NULL;
    readonly_source_fs = FALSE;

    common = &job->common;

    report_copy_progress (job, source_info, transfer_info);

    /* Query the source dir, not the file because if it's a symlink we'll follow it */
    source_dir = g_file_get_parent ((GFile *) job->files->data);
    if (source_dir)
    {
        inf = g_file_query_filesystem_info (source_dir, "filesystem::readonly", NULL, NULL);
        if (inf != NULL)
        {
            readonly_source_fs = g_file_info_get_attribute_boolean (inf, "filesystem::readonly");
            g_object_unref (inf);
        }
        g_object_unref (source_dir);
    }

    unique_names = (job->destination == NULL);
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

        if (job->destination)
        {
            dest = g_object_ref (job->destination);
        }
        else
        {
            dest = g_file_get_parent (src);
        }
        if (dest)
        {
            skipped_file = FALSE;
            copy_move_file (job, src, dest,
                            same_fs, unique_names,
                            &dest_fs_type,
                            source_info, transfer_info,
                            job->debuting_files,
                            point, FALSE, &skipped_file,
                            readonly_source_fs);
            g_object_unref (dest);

            if (skipped_file)
            {
                transfer_add_file_to_count (src, common, transfer_info);
                report_copy_progress (job, source_info, transfer_info);
            }
        }
        i++;
    }

    g_free (dest_fs_type);
}
