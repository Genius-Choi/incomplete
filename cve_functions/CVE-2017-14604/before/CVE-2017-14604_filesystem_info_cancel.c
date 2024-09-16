filesystem_info_cancel (NautilusDirectory *directory)
{
    if (directory->details->filesystem_info_state != NULL)
    {
        g_cancellable_cancel (directory->details->filesystem_info_state->cancellable);
        directory->details->filesystem_info_state->directory = NULL;
        directory->details->filesystem_info_state = NULL;
        async_job_end (directory, "filesystem info");
    }
}
