got_mount (MountState *state,
           GMount     *mount)
{
    NautilusDirectory *directory;
    NautilusFile *file;

    directory = nautilus_directory_ref (state->directory);

    state->directory->details->mount_state = NULL;
    async_job_end (state->directory, "mount");

    file = nautilus_file_ref (state->file);

    file->details->mount_is_up_to_date = TRUE;
    nautilus_file_set_mount (file, mount);

    nautilus_directory_async_state_changed (directory);
    nautilus_file_changed (file);

    nautilus_file_unref (file);

    nautilus_directory_unref (directory);

    mount_state_free (state);
}
