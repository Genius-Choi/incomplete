nautilus_file_operations_mount_volume_full (GtkWindow             *parent_window,
                                            GVolume               *volume,
                                            NautilusMountCallback  mount_callback,
                                            GObject               *mount_callback_data_object)
{
    GMountOperation *mount_op;

    mount_op = gtk_mount_operation_new (parent_window);
    g_mount_operation_set_password_save (mount_op, G_PASSWORD_SAVE_FOR_SESSION);
    g_object_set_data (G_OBJECT (mount_op),
                       "mount-callback",
                       mount_callback);

    if (mount_callback != NULL &&
        mount_callback_data_object != NULL)
    {
        g_object_weak_ref (mount_callback_data_object,
                           mount_callback_data_notify,
                           mount_op);
    }
    g_object_set_data (G_OBJECT (mount_op),
                       "mount-callback-data",
                       mount_callback_data_object);

    g_volume_mount (volume, 0, mount_op, NULL, volume_mount_cb, mount_op);
}
