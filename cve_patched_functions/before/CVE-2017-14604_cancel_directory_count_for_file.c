cancel_directory_count_for_file (NautilusDirectory *directory,
                                 NautilusFile      *file)
{
    if (directory->details->count_in_progress != NULL &&
        directory->details->count_in_progress->count_file == file)
    {
        directory_count_cancel (directory);
    }
}
