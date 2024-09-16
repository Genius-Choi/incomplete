get_trash_dirs_for_mount (GMount *mount)
{
    GFile *root;
    GFile *trash;
    char *relpath;
    GList *list;

    root = g_mount_get_root (mount);
    if (root == NULL)
    {
        return NULL;
    }

    list = NULL;

    if (g_file_is_native (root))
    {
        relpath = g_strdup_printf (".Trash/%d", getuid ());
        trash = g_file_resolve_relative_path (root, relpath);
        g_free (relpath);

        list = g_list_prepend (list, g_file_get_child (trash, "files"));
        list = g_list_prepend (list, g_file_get_child (trash, "info"));

        g_object_unref (trash);

        relpath = g_strdup_printf (".Trash-%d", getuid ());
        trash = g_file_get_child (root, relpath);
        g_free (relpath);

        list = g_list_prepend (list, g_file_get_child (trash, "files"));
        list = g_list_prepend (list, g_file_get_child (trash, "info"));

        g_object_unref (trash);
    }

    g_object_unref (root);

    return list;
}
