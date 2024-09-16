unmount_mount_callback (GObject      *source_object,
                        GAsyncResult *res,
                        gpointer      user_data)
{
    UnmountData *data = user_data;
    GError *error;
    char *primary;
    gboolean unmounted;

    error = NULL;
    if (data->eject)
    {
        unmounted = g_mount_eject_with_operation_finish (G_MOUNT (source_object),
                                                         res, &error);
    }
    else
    {
        unmounted = g_mount_unmount_with_operation_finish (G_MOUNT (source_object),
                                                           res, &error);
    }

    if (!unmounted)
    {
        if (error->code != G_IO_ERROR_FAILED_HANDLED)
        {
            if (data->eject)
            {
                primary = f (_("Unable to eject %V"), source_object);
            }
            else
            {
                primary = f (_("Unable to unmount %V"), source_object);
            }
            eel_show_error_dialog (primary,
                                   error->message,
                                   data->parent_window);
            g_free (primary);
        }
    }

    if (data->callback)
    {
        data->callback (data->callback_data);
    }

    if (error != NULL)
    {
        g_error_free (error);
    }

    unmount_data_free (data);
}
