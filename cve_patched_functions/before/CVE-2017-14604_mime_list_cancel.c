mime_list_cancel (NautilusDirectory *directory)
{
    if (directory->details->mime_list_in_progress != NULL)
    {
        g_cancellable_cancel (directory->details->mime_list_in_progress->cancellable);
    }
}
