mount_callback_data_notify (gpointer  data,
                            GObject  *object)
{
    GMountOperation *mount_op;

    mount_op = G_MOUNT_OPERATION (data);
    g_object_set_data (G_OBJECT (mount_op), "mount-callback", NULL);
    g_object_set_data (G_OBJECT (mount_op), "mount-callback-data", NULL);
}
