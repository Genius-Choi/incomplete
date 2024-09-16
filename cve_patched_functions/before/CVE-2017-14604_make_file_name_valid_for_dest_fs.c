make_file_name_valid_for_dest_fs (char       *filename,
                                  const char *dest_fs_type)
{
    if (dest_fs_type != NULL && filename != NULL)
    {
        if (!strcmp (dest_fs_type, "fat") ||
            !strcmp (dest_fs_type, "vfat") ||
            !strcmp (dest_fs_type, "msdos") ||
            !strcmp (dest_fs_type, "msdosfs"))
        {
            gboolean ret;
            int i, old_len;

            ret = fat_str_replace (filename, '_');

            old_len = strlen (filename);
            for (i = 0; i < old_len; i++)
            {
                if (filename[i] != ' ')
                {
                    g_strchomp (filename);
                    ret |= (old_len != strlen (filename));
                    break;
                }
            }

            return ret;
        }
    }

    return FALSE;
}
