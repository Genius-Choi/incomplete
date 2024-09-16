file_was_not_mounted (NautilusFile *file)
{
    GError *error;

    error = nautilus_file_get_file_info_error (file);
    return
        error != NULL &&
        error->domain == G_IO_ERROR &&
        error->code == G_IO_ERROR_NOT_MOUNTED;
}
