do_unmount (UnmountData *data)
{
    GMountOperation *mount_op;

    if (data->mount_operation)
    {
        mount_op = g_object_ref (data->mount_operation);
    }
    else
    {
        mount_op = gtk_mount_operation_new (data->parent_window);
    }
    if (data->eject)
    {
        g_mount_eject_with_operation (data->mount,
                                      0,
                                      mount_op,
                                      NULL,
                                      unmount_mount_callback,
                                      data);
    }
    else
    {
        g_mount_unmount_with_operation (data->mount,
                                        0,
                                        mount_op,
                                        NULL,
                                        unmount_mount_callback,
                                        data);
    }
    g_object_unref (mount_op);
}
