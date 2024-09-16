cancel_deep_counts_for_file (NautilusDirectory *directory,
                             NautilusFile      *file)
{
    if (directory->details->deep_count_file == file)
    {
        deep_count_cancel (directory);
    }
}
