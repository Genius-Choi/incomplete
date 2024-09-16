get_abs_path_for_symlink (GFile *file,
                          GFile *destination)
{
    GFile *root, *parent;
    char *relative, *abs;

    if (g_file_is_native (file) || g_file_is_native (destination))
    {
        return g_file_get_path (file);
    }

    root = g_object_ref (file);
    while ((parent = g_file_get_parent (root)) != NULL)
    {
        g_object_unref (root);
        root = parent;
    }

    relative = g_file_get_relative_path (root, file);
    g_object_unref (root);
    abs = g_strconcat ("/", relative, NULL);
    g_free (relative);
    return abs;
}
