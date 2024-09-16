get_mount_at (GFile *target)
{
    GVolumeMonitor *monitor;
    GFile *root;
    GList *mounts, *l;
    GMount *found;

    monitor = g_volume_monitor_get ();
    mounts = g_volume_monitor_get_mounts (monitor);

    found = NULL;
    for (l = mounts; l != NULL; l = l->next)
    {
        GMount *mount = G_MOUNT (l->data);

        if (g_mount_is_shadowed (mount))
        {
            continue;
        }

        root = g_mount_get_root (mount);

        if (g_file_equal (target, root))
        {
            found = g_object_ref (mount);
            break;
        }

        g_object_unref (root);
    }

    g_list_free_full (mounts, g_object_unref);

    g_object_unref (monitor);

    return found;
}
