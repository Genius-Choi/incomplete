nautilus_mime_file_extracts (NautilusFile *file)
{
    return get_activation_action (file) == ACTIVATION_ACTION_EXTRACT;
}
