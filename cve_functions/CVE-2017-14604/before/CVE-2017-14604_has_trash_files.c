has_trash_files (GMount *mount)
{
    GList *dirs, *l;
    GFile *dir;
    gboolean res;

    dirs = get_trash_dirs_for_mount (mount);

    res = FALSE;

    for (l = dirs; l != NULL; l = l->next)
    {
        dir = l->data;

        if (dir_has_files (dir))
        {
            res = TRUE;
            break;
        }
    }

    g_list_free_full (dirs, g_object_unref);

    return res;
}
