file_was_cancelled (NautilusFile *file)
{
    GError *error;

    error = nautilus_file_get_file_info_error (file);
    return
        error != NULL &&
        error->domain == G_IO_ERROR &&
        error->code == G_IO_ERROR_CANCELLED;
}
