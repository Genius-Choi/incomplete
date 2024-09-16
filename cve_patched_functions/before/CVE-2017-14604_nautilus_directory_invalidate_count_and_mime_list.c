nautilus_directory_invalidate_count_and_mime_list (NautilusDirectory *directory)
{
    NautilusFile *file;

    file = nautilus_directory_get_existing_corresponding_file (directory);
    if (file != NULL)
    {
        nautilus_file_invalidate_count_and_mime_list (file);
    }

    nautilus_file_unref (file);
}
