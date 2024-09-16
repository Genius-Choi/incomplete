is_dir (GFile *file)
{
    GFileInfo *info;
    gboolean res;

    res = FALSE;
    info = g_file_query_info (file,
                              G_FILE_ATTRIBUTE_STANDARD_TYPE,
                              G_FILE_QUERY_INFO_NOFOLLOW_SYMLINKS,
                              NULL, NULL);
    if (info)
    {
        res = g_file_info_get_file_type (info) == G_FILE_TYPE_DIRECTORY;
        g_object_unref (info);
    }

    return res;
}
