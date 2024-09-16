finish_info_provider (NautilusDirectory    *directory,
                      NautilusFile         *file,
                      NautilusInfoProvider *provider)
{
    file->details->pending_info_providers =
        g_list_remove (file->details->pending_info_providers,
                       provider);
    g_object_unref (provider);

    nautilus_directory_async_state_changed (directory);

    if (file->details->pending_info_providers == NULL)
    {
        nautilus_file_info_providers_done (file);
    }
}
