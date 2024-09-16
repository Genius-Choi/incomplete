filesystem_info_start (NautilusDirectory *directory,
                       NautilusFile      *file,
                       gboolean          *doing_io)
{
    GFile *location;
    FilesystemInfoState *state;

    if (directory->details->filesystem_info_state != NULL)
    {
        *doing_io = TRUE;
        return;
    }

    if (!is_needy (file,
                   lacks_filesystem_info,
                   REQUEST_FILESYSTEM_INFO))
    {
        return;
    }
    *doing_io = TRUE;

    if (!async_job_start (directory, "filesystem info"))
    {
        return;
    }

    state = g_new0 (FilesystemInfoState, 1);
    state->directory = directory;
    state->file = file;
    state->cancellable = g_cancellable_new ();

    location = nautilus_file_get_location (file);

    directory->details->filesystem_info_state = state;

    g_file_query_filesystem_info_async (location,
                                        G_FILE_ATTRIBUTE_FILESYSTEM_READONLY ","
                                        G_FILE_ATTRIBUTE_FILESYSTEM_USE_PREVIEW ","
                                        G_FILE_ATTRIBUTE_FILESYSTEM_TYPE,
                                        G_PRIORITY_DEFAULT,
                                        state->cancellable,
                                        query_filesystem_info_callback,
                                        state);
    g_object_unref (location);
}
