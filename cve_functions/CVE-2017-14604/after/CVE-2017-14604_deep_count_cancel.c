deep_count_cancel (NautilusDirectory *directory)
{
    if (directory->details->deep_count_in_progress != NULL)
    {
        g_assert (NAUTILUS_IS_FILE (directory->details->deep_count_file));

        g_cancellable_cancel (directory->details->deep_count_in_progress->cancellable);

        directory->details->deep_count_file->details->deep_counts_status = NAUTILUS_REQUEST_NOT_STARTED;

        directory->details->deep_count_in_progress->directory = NULL;
        directory->details->deep_count_in_progress = NULL;
        directory->details->deep_count_file = NULL;

        async_job_end (directory, "deep count");
    }
}
