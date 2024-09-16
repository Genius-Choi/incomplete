activate_mount_op_active (GtkMountOperation  *operation,
                          GParamSpec         *pspec,
                          ActivateParameters *parameters)
{
    gboolean is_active;

    g_object_get (operation, "is-showing", &is_active, NULL);

    if (is_active)
    {
        pause_activation_timed_cancel (parameters);
    }
    else
    {
        unpause_activation_timed_cancel (parameters);
    }
}
