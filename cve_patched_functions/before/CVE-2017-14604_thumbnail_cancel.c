thumbnail_cancel (NautilusDirectory *directory)
{
    if (directory->details->thumbnail_state != NULL)
    {
        g_cancellable_cancel (directory->details->thumbnail_state->cancellable);
        directory->details->thumbnail_state->directory = NULL;
        directory->details->thumbnail_state = NULL;
        async_job_end (directory, "thumbnail");
    }
}
