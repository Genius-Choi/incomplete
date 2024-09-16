has_fs_id (GFile      *file,
           const char *fs_id)
{
    const char *id;
    GFileInfo *info;
    gboolean res;

    res = FALSE;
    info = g_file_query_info (file,
                              G_FILE_ATTRIBUTE_ID_FILESYSTEM,
                              G_FILE_QUERY_INFO_NOFOLLOW_SYMLINKS,
                              NULL, NULL);

    if (info)
    {
        id = g_file_info_get_attribute_string (info, G_FILE_ATTRIBUTE_ID_FILESYSTEM);

        if (id && strcmp (id, fs_id) == 0)
        {
            res = TRUE;
        }

        g_object_unref (info);
    }

    return res;
}
