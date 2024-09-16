get_target_file_for_display_name (GFile       *dir,
                                  const gchar *name)
{
    GFile *dest;

    dest = NULL;
    dest = g_file_get_child_for_display_name (dir, name, NULL);

    if (dest == NULL)
    {
        dest = g_file_get_child (dir, name);
    }

    return dest;
}
