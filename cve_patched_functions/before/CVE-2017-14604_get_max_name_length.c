get_max_name_length (GFile *file_dir)
{
    int max_length;
    char *dir;
    long max_path;
    long max_name;

    max_length = -1;

    if (!g_file_has_uri_scheme (file_dir, "file"))
    {
        return max_length;
    }

    dir = g_file_get_path (file_dir);
    if (!dir)
    {
        return max_length;
    }

    max_path = pathconf (dir, _PC_PATH_MAX);
    max_name = pathconf (dir, _PC_NAME_MAX);

    if (max_name == -1 && max_path == -1)
    {
        max_length = -1;
    }
    else if (max_name == -1 && max_path != -1)
    {
        max_length = max_path - (strlen (dir) + 1);
    }
    else if (max_name != -1 && max_path == -1)
    {
        max_length = max_name;
    }
    else
    {
        int leftover;

        leftover = max_path - (strlen (dir) + 1);

        max_length = MIN (leftover, max_name);
    }

    g_free (dir);

    return max_length;
}
