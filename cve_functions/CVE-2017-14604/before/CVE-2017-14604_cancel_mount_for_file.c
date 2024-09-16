cancel_mount_for_file (NautilusDirectory *directory,
                       NautilusFile      *file)
{
    if (directory->details->mount_state != NULL &&
        directory->details->mount_state->file == file)
    {
        mount_cancel (directory);
    }
}
