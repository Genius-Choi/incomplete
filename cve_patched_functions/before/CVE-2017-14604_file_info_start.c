file_info_start (NautilusDirectory *directory,
                 NautilusFile      *file,
                 gboolean          *doing_io)
{
    GFile *location;
    GetInfoState *state;

    file_info_stop (directory);

    if (directory->details->get_info_in_progress != NULL)
    {
        *doing_io = TRUE;
        return;
    }

    if (!is_needy (file, lacks_info, REQUEST_FILE_INFO))
    {
        return;
    }
    *doing_io = TRUE;

    if (!async_job_start (directory, "file info"))
    {
        return;
    }

    directory->details->get_info_file = file;
    file->details->get_info_failed = FALSE;
    if (file->details->get_info_error)
    {
        g_error_free (file->details->get_info_error);
        file->details->get_info_error = NULL;
    }

    state = g_new (GetInfoState, 1);
    state->directory = directory;
    state->cancellable = g_cancellable_new ();

    directory->details->get_info_in_progress = state;

    location = nautilus_file_get_location (file);
    g_file_query_info_async (location,
                             NAUTILUS_FILE_DEFAULT_ATTRIBUTES,
                             0,
                             G_PRIORITY_DEFAULT,
                             state->cancellable, query_info_callback, state);
    g_object_unref (location);
}
