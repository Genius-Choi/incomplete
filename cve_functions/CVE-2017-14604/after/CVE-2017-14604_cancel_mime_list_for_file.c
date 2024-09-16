cancel_mime_list_for_file (NautilusDirectory *directory,
                           NautilusFile      *file)
{
    if (directory->details->mime_list_in_progress != NULL &&
        directory->details->mime_list_in_progress->mime_list_file == file)
    {
        mime_list_cancel (directory);
    }
}
