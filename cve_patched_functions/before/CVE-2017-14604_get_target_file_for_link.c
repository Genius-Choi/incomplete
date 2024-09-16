get_target_file_for_link (GFile      *src,
                          GFile      *dest_dir,
                          const char *dest_fs_type,
                          int         count)
{
    const char *editname;
    char *basename, *new_name;
    GFileInfo *info;
    GFile *dest;
    int max_length;

    max_length = get_max_name_length (dest_dir);

    dest = NULL;
    info = g_file_query_info (src,
                              G_FILE_ATTRIBUTE_STANDARD_EDIT_NAME,
                              0, NULL, NULL);
    if (info != NULL)
    {
        editname = g_file_info_get_attribute_string (info, G_FILE_ATTRIBUTE_STANDARD_EDIT_NAME);

        if (editname != NULL)
        {
            new_name = get_link_name (editname, count, max_length);
            make_file_name_valid_for_dest_fs (new_name, dest_fs_type);
            dest = g_file_get_child_for_display_name (dest_dir, new_name, NULL);
            g_free (new_name);
        }

        g_object_unref (info);
    }

    if (dest == NULL)
    {
        basename = g_file_get_basename (src);
        make_file_name_valid_for_dest_fs (basename, dest_fs_type);

        if (g_utf8_validate (basename, -1, NULL))
        {
            new_name = get_link_name (basename, count, max_length);
            make_file_name_valid_for_dest_fs (new_name, dest_fs_type);
            dest = g_file_get_child_for_display_name (dest_dir, new_name, NULL);
            g_free (new_name);
        }

        if (dest == NULL)
        {
            if (count == 1)
            {
                new_name = g_strdup_printf ("%s.lnk", basename);
            }
            else
            {
                new_name = g_strdup_printf ("%s.lnk%d", basename, count);
            }
            make_file_name_valid_for_dest_fs (new_name, dest_fs_type);
            dest = g_file_get_child (dest_dir, new_name);
            g_free (new_name);
        }

        g_free (basename);
    }

    return dest;
}
