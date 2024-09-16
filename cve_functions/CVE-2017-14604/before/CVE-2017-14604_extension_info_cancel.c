extension_info_cancel (NautilusDirectory *directory)
{
    if (directory->details->extension_info_in_progress != NULL)
    {
        if (directory->details->extension_info_idle)
        {
            g_source_remove (directory->details->extension_info_idle);
        }
        else
        {
            nautilus_info_provider_cancel_update
                (directory->details->extension_info_provider,
                directory->details->extension_info_in_progress);
        }

        directory->details->extension_info_in_progress = NULL;
        directory->details->extension_info_file = NULL;
        directory->details->extension_info_provider = NULL;
        directory->details->extension_info_idle = 0;

        async_job_end (directory, "extension info");
    }
}
