cancel_file_info_for_file (NautilusDirectory *directory,
                           NautilusFile      *file)
{
    if (directory->details->get_info_file == file)
    {
        file_info_cancel (directory);
    }
}
