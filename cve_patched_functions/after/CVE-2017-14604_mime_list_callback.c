mime_list_callback (GObject      *source_object,
                    GAsyncResult *res,
                    gpointer      user_data)
{
    MimeListState *state;
    NautilusDirectory *directory;
    GError *error;
    GList *files, *l;
    GFileInfo *info;

    state = user_data;
    directory = state->directory;

    if (g_cancellable_is_cancelled (state->cancellable))
    {
        /* Operation was cancelled. Bail out */
        directory->details->mime_list_in_progress = NULL;

        async_job_end (directory, "MIME list");
        nautilus_directory_async_state_changed (directory);

        mime_list_state_free (state);

        return;
    }

    g_assert (directory->details->mime_list_in_progress != NULL);
    g_assert (directory->details->mime_list_in_progress == state);

    error = NULL;
    files = g_file_enumerator_next_files_finish (state->enumerator,
                                                 res, &error);

    for (l = files; l != NULL; l = l->next)
    {
        info = l->data;
        mime_list_one (state, info);
        g_object_unref (info);
    }

    if (files == NULL)
    {
        mime_list_done (state, error != NULL);
        mime_list_state_free (state);
    }
    else
    {
        g_file_enumerator_next_files_async (state->enumerator,
                                            DIRECTORY_LOAD_ITEMS_PER_CALLBACK,
                                            G_PRIORITY_DEFAULT,
                                            state->cancellable,
                                            mime_list_callback,
                                            state);
    }

    g_list_free (files);

    if (error)
    {
        g_error_free (error);
    }
}
