directory_count_cancel (NautilusDirectory *directory)
{
    if (directory->details->count_in_progress != NULL)
    {
        g_cancellable_cancel (directory->details->count_in_progress->cancellable);
        directory->details->count_in_progress = NULL;
    }
}
