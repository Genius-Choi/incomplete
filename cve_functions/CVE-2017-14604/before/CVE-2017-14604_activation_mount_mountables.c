activation_mount_mountables (ActivateParameters *parameters)
{
    NautilusFile *file;
    GMountOperation *mount_op;

    if (parameters->mountables != NULL)
    {
        file = parameters->mountables->data;
        mount_op = gtk_mount_operation_new (parameters->parent_window);
        g_mount_operation_set_password_save (mount_op, G_PASSWORD_SAVE_FOR_SESSION);
        g_signal_connect (mount_op, "notify::is-showing",
                          G_CALLBACK (activate_mount_op_active), parameters);
        nautilus_file_mount (file,
                             mount_op,
                             parameters->cancellable,
                             activation_mountable_mounted,
                             parameters);
        g_object_unref (mount_op);
        return;
    }

    if (parameters->mountables == NULL && parameters->start_mountables == NULL)
    {
        activation_get_activation_uris (parameters);
    }
}
