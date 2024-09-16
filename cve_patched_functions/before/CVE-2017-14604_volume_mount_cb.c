volume_mount_cb (GObject      *source_object,
                 GAsyncResult *res,
                 gpointer      user_data)
{
    NautilusMountCallback mount_callback;
    GObject *mount_callback_data_object;
    GMountOperation *mount_op = user_data;
    GError *error;
    char *primary;
    char *name;
    gboolean success;

    success = TRUE;
    error = NULL;
    if (!g_volume_mount_finish (G_VOLUME (source_object), res, &error))
    {
        if (error->code != G_IO_ERROR_FAILED_HANDLED &&
            error->code != G_IO_ERROR_ALREADY_MOUNTED)
        {
            GtkWindow *parent;

            parent = gtk_mount_operation_get_parent (GTK_MOUNT_OPERATION (mount_op));
            name = g_volume_get_name (G_VOLUME (source_object));
            primary = g_strdup_printf (_("Unable to access “%s”"), name);
            g_free (name);
            success = FALSE;
            eel_show_error_dialog (primary,
                                   error->message,
                                   parent);
            g_free (primary);
        }
        g_error_free (error);
    }

    mount_callback = (NautilusMountCallback)
                     g_object_get_data (G_OBJECT (mount_op), "mount-callback");
    mount_callback_data_object =
        g_object_get_data (G_OBJECT (mount_op), "mount-callback-data");

    if (mount_callback != NULL)
    {
        (*mount_callback)(G_VOLUME (source_object),
                          success,
                          mount_callback_data_object);

        if (mount_callback_data_object != NULL)
        {
            g_object_weak_unref (mount_callback_data_object,
                                 mount_callback_data_notify,
                                 mount_op);
        }
    }

    g_object_unref (mount_op);
}
