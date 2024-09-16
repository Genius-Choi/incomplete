activation_start_mountables (ActivateParameters *parameters)
{
    NautilusFile *file;
    GMountOperation *start_op;

    if (parameters->start_mountables != NULL)
    {
        file = parameters->start_mountables->data;
        start_op = gtk_mount_operation_new (parameters->parent_window);
        g_signal_connect (start_op, "notify::is-showing",
                          G_CALLBACK (activate_mount_op_active), parameters);
        nautilus_file_start (file,
                             start_op,
                             parameters->cancellable,
                             activation_mountable_started,
                             parameters);
        g_object_unref (start_op);
        return;
    }

    if (parameters->mountables == NULL && parameters->start_mountables == NULL)
    {
        activation_get_activation_uris (parameters);
    }
}
