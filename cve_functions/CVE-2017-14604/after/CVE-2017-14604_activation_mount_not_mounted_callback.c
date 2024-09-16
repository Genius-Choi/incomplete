activation_mount_not_mounted_callback (GObject      *source_object,
                                       GAsyncResult *res,
                                       gpointer      user_data)
{
    ActivateParameters *parameters = user_data;
    GError *error;
    NautilusFile *file;
    LaunchLocation *loc;

    file = parameters->not_mounted->data;

    error = NULL;
    if (!g_file_mount_enclosing_volume_finish (G_FILE (source_object), res, &error))
    {
        if (error->domain != G_IO_ERROR ||
            (error->code != G_IO_ERROR_CANCELLED &&
             error->code != G_IO_ERROR_FAILED_HANDLED &&
             error->code != G_IO_ERROR_ALREADY_MOUNTED))
        {
            eel_show_error_dialog (_("Unable to access location"), error->message, parameters->parent_window);
        }

        if (error->domain != G_IO_ERROR ||
            error->code != G_IO_ERROR_ALREADY_MOUNTED)
        {
            loc = find_launch_location_for_file (parameters->locations,
                                                 file);
            if (loc)
            {
                parameters->locations =
                    g_list_remove (parameters->locations, loc);
                launch_location_free (loc);
            }
        }

        g_error_free (error);
    }

    parameters->not_mounted = g_list_delete_link (parameters->not_mounted,
                                                  parameters->not_mounted);
    nautilus_file_unref (file);

    activation_mount_not_mounted (parameters);
}
