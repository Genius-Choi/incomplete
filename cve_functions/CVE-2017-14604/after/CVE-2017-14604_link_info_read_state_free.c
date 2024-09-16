link_info_read_state_free (LinkInfoReadState *state)
{
    g_object_unref (state->cancellable);
    g_free (state);
}
