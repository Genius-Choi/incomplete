directory_load_state_free (DirectoryLoadState *state)
{
    if (state->enumerator)
    {
        if (!g_file_enumerator_is_closed (state->enumerator))
        {
            g_file_enumerator_close_async (state->enumerator,
                                           0, NULL, NULL, NULL);
        }
        g_object_unref (state->enumerator);
    }

    if (state->load_mime_list_hash != NULL)
    {
        istr_set_destroy (state->load_mime_list_hash);
    }
    nautilus_file_unref (state->load_directory_file);
    g_object_unref (state->cancellable);
    g_free (state);
}
