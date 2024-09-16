dir_has_files (GFile *dir)
{
    GFileEnumerator *enumerator;
    gboolean res;
    GFileInfo *file_info;

    res = FALSE;

    enumerator = g_file_enumerate_children (dir,
                                            G_FILE_ATTRIBUTE_STANDARD_NAME,
                                            0,
                                            NULL, NULL);
    if (enumerator)
    {
        file_info = g_file_enumerator_next_file (enumerator, NULL, NULL);
        if (file_info != NULL)
        {
            res = TRUE;
            g_object_unref (file_info);
        }

        g_file_enumerator_close (enumerator, NULL, NULL);
        g_object_unref (enumerator);
    }


    return res;
}
