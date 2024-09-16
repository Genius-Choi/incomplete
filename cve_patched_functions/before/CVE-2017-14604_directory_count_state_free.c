directory_count_state_free (DirectoryCountState *state)
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
    g_object_unref (state->cancellable);
    nautilus_directory_unref (state->directory);
    g_free (state);
}
