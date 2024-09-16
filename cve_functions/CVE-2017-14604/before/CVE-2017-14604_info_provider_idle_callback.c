info_provider_idle_callback (gpointer user_data)
{
    InfoProviderResponse *response;
    NautilusDirectory *directory;

    response = user_data;
    directory = response->directory;

    if (response->handle != directory->details->extension_info_in_progress
        || response->provider != directory->details->extension_info_provider)
    {
        g_warning ("Unexpected plugin response.  This probably indicates a bug in a Nautilus extension: handle=%p", response->handle);
    }
    else
    {
        NautilusFile *file;
        async_job_end (directory, "extension info");

        file = directory->details->extension_info_file;

        directory->details->extension_info_file = NULL;
        directory->details->extension_info_provider = NULL;
        directory->details->extension_info_in_progress = NULL;
        directory->details->extension_info_idle = 0;

        finish_info_provider (directory, file, response->provider);
    }

    return FALSE;
}
