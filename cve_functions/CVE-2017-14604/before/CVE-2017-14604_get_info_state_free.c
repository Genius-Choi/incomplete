get_info_state_free (GetInfoState *state)
{
    g_object_unref (state->cancellable);
    g_free (state);
}
