thumbnail_state_free (ThumbnailState *state)
{
    g_object_unref (state->cancellable);
    g_free (state);
}
