deep_count_state_free (DeepCountState *state)
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
    if (state->deep_count_location)
    {
        g_object_unref (state->deep_count_location);
    }
    g_list_free_full (state->deep_count_subdirectories, g_object_unref);
    g_array_free (state->seen_deep_count_inodes, TRUE);
    g_free (state->fs_id);
    g_free (state);
}
