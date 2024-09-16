delete_trash_file (CommonJob *job,
                   GFile     *file,
                   gboolean   del_file,
                   gboolean   del_children)
{
    GFileInfo *info;
    GFile *child;
    GFileEnumerator *enumerator;

    if (job_aborted (job))
    {
        return;
    }

    if (del_children)
    {
        enumerator = g_file_enumerate_children (file,
                                                G_FILE_ATTRIBUTE_STANDARD_NAME ","
                                                G_FILE_ATTRIBUTE_STANDARD_TYPE,
                                                G_FILE_QUERY_INFO_NOFOLLOW_SYMLINKS,
                                                job->cancellable,
                                                NULL);
        if (enumerator)
        {
            while (!job_aborted (job) &&
                   (info = g_file_enumerator_next_file (enumerator, job->cancellable, NULL)) != NULL)
            {
                child = g_file_get_child (file,
                                          g_file_info_get_name (info));
                delete_trash_file (job, child, TRUE,
                                   g_file_info_get_file_type (info) == G_FILE_TYPE_DIRECTORY);
                g_object_unref (child);
                g_object_unref (info);
            }
            g_file_enumerator_close (enumerator, job->cancellable, NULL);
            g_object_unref (enumerator);
        }
    }

    if (!job_aborted (job) && del_file)
    {
        g_file_delete (file, job->cancellable, NULL);
    }
}
