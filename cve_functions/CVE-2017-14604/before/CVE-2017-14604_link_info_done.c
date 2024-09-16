link_info_done (NautilusDirectory *directory,
                NautilusFile      *file,
                const char        *uri,
                const char        *name,
                GIcon             *icon,
                gboolean           is_launcher,
                gboolean           is_foreign)
{
    gboolean is_trusted;

    file->details->link_info_is_up_to_date = TRUE;

    is_trusted = is_link_trusted (file, is_launcher);

    if (is_trusted)
    {
        nautilus_file_set_display_name (file, name, name, TRUE);
    }
    else
    {
        nautilus_file_set_display_name (file, NULL, NULL, TRUE);
    }

    file->details->got_link_info = TRUE;
    g_clear_object (&file->details->custom_icon);

    if (uri)
    {
        g_free (file->details->activation_uri);
        file->details->activation_uri = NULL;
        file->details->got_custom_activation_uri = TRUE;
        file->details->activation_uri = g_strdup (uri);
    }
    if (is_trusted && (icon != NULL))
    {
        file->details->custom_icon = g_object_ref (icon);
    }
    file->details->is_launcher = is_launcher;
    file->details->is_foreign_link = is_foreign;
    file->details->is_trusted_link = is_trusted;

    nautilus_directory_async_state_changed (directory);
}
