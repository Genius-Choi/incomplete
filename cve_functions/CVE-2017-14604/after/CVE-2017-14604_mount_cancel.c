mount_cancel (NautilusDirectory *directory)
{
    if (directory->details->mount_state != NULL)
    {
        g_cancellable_cancel (directory->details->mount_state->cancellable);
        directory->details->mount_state->directory = NULL;
        directory->details->mount_state = NULL;
        async_job_end (directory, "mount");
    }
}
