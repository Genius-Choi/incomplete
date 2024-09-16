cancel_link_info_for_file (NautilusDirectory *directory,
                           NautilusFile      *file)
{
    if (directory->details->link_info_read_state != NULL &&
        directory->details->link_info_read_state->file == file)
    {
        link_info_cancel (directory);
    }
}
