link_info_cancel (NautilusDirectory *directory)
{
    if (directory->details->link_info_read_state != NULL)
    {
        g_cancellable_cancel (directory->details->link_info_read_state->cancellable);
        directory->details->link_info_read_state->directory = NULL;
        directory->details->link_info_read_state = NULL;
        async_job_end (directory, "link info");
    }
}
