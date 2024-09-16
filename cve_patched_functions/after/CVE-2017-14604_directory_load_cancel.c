directory_load_cancel (NautilusDirectory *directory)
{
    NautilusFile *file;
    DirectoryLoadState *state;

    state = directory->details->directory_load_in_progress;
    if (state != NULL)
    {
        file = state->load_directory_file;
        file->details->loading_directory = FALSE;
        if (file->details->directory != directory)
        {
            nautilus_directory_async_state_changed (file->details->directory);
        }

        g_cancellable_cancel (state->cancellable);
        state->directory = NULL;
        directory->details->directory_load_in_progress = NULL;
        async_job_end (directory, "file list");
    }
}
