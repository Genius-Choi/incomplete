activation_parameters_free (ActivateParameters *parameters)
{
    if (parameters->timed_wait_active)
    {
        eel_timed_wait_stop (cancel_activate_callback, parameters);
    }

    if (parameters->slot)
    {
        g_object_remove_weak_pointer (G_OBJECT (parameters->slot), (gpointer *) &parameters->slot);
    }
    if (parameters->parent_window)
    {
        g_object_remove_weak_pointer (G_OBJECT (parameters->parent_window), (gpointer *) &parameters->parent_window);
    }
    g_object_unref (parameters->cancellable);
    launch_location_list_free (parameters->locations);
    nautilus_file_list_free (parameters->mountables);
    nautilus_file_list_free (parameters->start_mountables);
    nautilus_file_list_free (parameters->not_mounted);
    g_free (parameters->activation_directory);
    g_free (parameters->timed_wait_prompt);
    g_assert (parameters->files_handle == NULL);
    g_free (parameters);
}
