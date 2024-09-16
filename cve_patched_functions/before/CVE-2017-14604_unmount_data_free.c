unmount_data_free (UnmountData *data)
{
    if (data->parent_window)
    {
        g_object_remove_weak_pointer (G_OBJECT (data->parent_window),
                                      (gpointer *) &data->parent_window);
    }

    g_clear_object (&data->mount_operation);
    g_object_unref (data->mount);
    g_free (data);
}
