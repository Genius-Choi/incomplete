nautilus_mime_actions_check_if_required_attributes_ready (NautilusFile *file)
{
    NautilusFileAttributes attributes;
    gboolean ready;

    attributes = nautilus_mime_actions_get_required_file_attributes ();
    ready = nautilus_file_check_if_ready (file, attributes);

    return ready;
}
