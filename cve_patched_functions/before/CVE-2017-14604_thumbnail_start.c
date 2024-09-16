thumbnail_start (NautilusDirectory *directory,
                 NautilusFile      *file,
                 gboolean          *doing_io)
{
    GFile *location;
    ThumbnailState *state;

    if (directory->details->thumbnail_state != NULL)
    {
        *doing_io = TRUE;
        return;
    }

    if (!is_needy (file,
                   lacks_thumbnail,
                   REQUEST_THUMBNAIL))
    {
        return;
    }
    *doing_io = TRUE;

    if (!async_job_start (directory, "thumbnail"))
    {
        return;
    }

    state = g_new0 (ThumbnailState, 1);
    state->directory = directory;
    state->file = file;
    state->cancellable = g_cancellable_new ();

    if (file->details->thumbnail_wants_original)
    {
        state->tried_original = TRUE;
        state->trying_original = TRUE;
        location = nautilus_file_get_location (file);
    }
    else
    {
        location = g_file_new_for_path (file->details->thumbnail_path);
    }

    directory->details->thumbnail_state = state;

    g_file_load_contents_async (location,
                                state->cancellable,
                                thumbnail_read_callback,
                                state);
    g_object_unref (location);
}
