mount_start (NautilusDirectory *directory,
             NautilusFile      *file,
             gboolean          *doing_io)
{
    GFile *location;
    MountState *state;

    if (directory->details->mount_state != NULL)
    {
        *doing_io = TRUE;
        return;
    }

    if (!is_needy (file,
                   lacks_mount,
                   REQUEST_MOUNT))
    {
        return;
    }
    *doing_io = TRUE;

    if (!async_job_start (directory, "mount"))
    {
        return;
    }

    state = g_new0 (MountState, 1);
    state->directory = directory;
    state->file = file;
    state->cancellable = g_cancellable_new ();

    location = nautilus_file_get_location (file);

    directory->details->mount_state = state;

    if (file->details->type == G_FILE_TYPE_MOUNTABLE)
    {
        GFile *target;
        GMount *mount;

        mount = NULL;
        target = nautilus_file_get_activation_location (file);
        if (target != NULL)
        {
            mount = get_mount_at (target);
            g_object_unref (target);
        }

        got_mount (state, mount);

        if (mount)
        {
            g_object_unref (mount);
        }
    }
    else
    {
        g_file_find_enclosing_mount_async (location,
                                           G_PRIORITY_DEFAULT,
                                           state->cancellable,
                                           find_enclosing_mount_callback,
                                           state);
    }
    g_object_unref (location);
}
