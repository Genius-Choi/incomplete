activate_callback (GList    *files,
                   gpointer  callback_data)
{
    ActivateParameters *parameters = callback_data;
    GList *l, *next;
    NautilusFile *file;
    LaunchLocation *location;

    parameters->files_handle = NULL;

    for (l = parameters->locations; l != NULL; l = next)
    {
        location = l->data;
        file = location->file;
        next = l->next;

        if (file_was_cancelled (file))
        {
            launch_location_free (location);
            parameters->locations = g_list_delete_link (parameters->locations, l);
            continue;
        }

        if (file_was_not_mounted (file))
        {
            if (parameters->tried_mounting)
            {
                launch_location_free (location);
                parameters->locations = g_list_delete_link (parameters->locations, l);
            }
            else
            {
                parameters->not_mounted = g_list_prepend (parameters->not_mounted,
                                                          nautilus_file_ref (file));
            }
            continue;
        }
    }


    if (parameters->not_mounted != NULL)
    {
        activation_mount_not_mounted (parameters);
    }
    else
    {
        activate_files (parameters);
    }
}
