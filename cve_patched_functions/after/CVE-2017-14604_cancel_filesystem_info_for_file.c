cancel_filesystem_info_for_file (NautilusDirectory *directory,
                                 NautilusFile      *file)
{
    if (directory->details->filesystem_info_state != NULL &&
        directory->details->filesystem_info_state->file == file)
    {
        filesystem_info_cancel (directory);
    }
}
