show_hidden_files_changed_callback (gpointer callback_data)
{
    show_hidden_files = g_settings_get_boolean (gtk_filechooser_preferences, NAUTILUS_PREFERENCES_SHOW_HIDDEN_FILES);
}
