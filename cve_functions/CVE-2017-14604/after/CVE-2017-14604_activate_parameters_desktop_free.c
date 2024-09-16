activate_parameters_desktop_free (ActivateParametersDesktop *parameters_desktop)
{
    if (parameters_desktop->parent_window)
    {
        g_object_remove_weak_pointer (G_OBJECT (parameters_desktop->parent_window), (gpointer *) &parameters_desktop->parent_window);
    }
    nautilus_file_unref (parameters_desktop->file);
    g_free (parameters_desktop);
}
