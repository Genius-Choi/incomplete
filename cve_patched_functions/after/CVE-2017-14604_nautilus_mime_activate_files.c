nautilus_mime_activate_files (GtkWindow               *parent_window,
                              NautilusWindowSlot      *slot,
                              GList                   *files,
                              const char              *launch_directory,
                              NautilusWindowOpenFlags  flags,
                              gboolean                 user_confirmation)
{
    ActivateParameters *parameters;
    char *file_name;
    int file_count;
    GList *l, *next;
    NautilusFile *file;
    LaunchLocation *location;

    if (files == NULL)
    {
        return;
    }

    DEBUG_FILES (files, "Calling activate_files() with files:");

    parameters = g_new0 (ActivateParameters, 1);
    parameters->slot = slot;
    g_object_add_weak_pointer (G_OBJECT (parameters->slot), (gpointer *) &parameters->slot);
    if (parent_window)
    {
        parameters->parent_window = parent_window;
        g_object_add_weak_pointer (G_OBJECT (parameters->parent_window), (gpointer *) &parameters->parent_window);
    }
    parameters->cancellable = g_cancellable_new ();
    parameters->activation_directory = g_strdup (launch_directory);
    parameters->locations = launch_locations_from_file_list (files);
    parameters->flags = flags;
    parameters->user_confirmation = user_confirmation;

    file_count = g_list_length (files);
    if (file_count == 1)
    {
        file_name = nautilus_file_get_display_name (files->data);
        parameters->timed_wait_prompt = g_strdup_printf (_("Opening “%s”."), file_name);
        g_free (file_name);
    }
    else
    {
        parameters->timed_wait_prompt = g_strdup_printf (ngettext ("Opening %d item.",
                                                                   "Opening %d items.",
                                                                   file_count),
                                                         file_count);
    }


    for (l = parameters->locations; l != NULL; l = next)
    {
        location = l->data;
        file = location->file;
        next = l->next;

        if (nautilus_file_can_mount (file))
        {
            parameters->mountables = g_list_prepend (parameters->mountables,
                                                     nautilus_file_ref (file));
        }

        if (nautilus_file_can_start (file))
        {
            parameters->start_mountables = g_list_prepend (parameters->start_mountables,
                                                           nautilus_file_ref (file));
        }
    }

    activation_start_timed_cancel (parameters);
    if (parameters->mountables != NULL)
    {
        activation_mount_mountables (parameters);
    }
    if (parameters->start_mountables != NULL)
    {
        activation_start_mountables (parameters);
    }
    if (parameters->mountables == NULL && parameters->start_mountables == NULL)
    {
        activation_get_activation_uris (parameters);
    }
}
