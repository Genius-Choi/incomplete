nautilus_directory_invalidate_file_attributes (NautilusDirectory      *directory,
                                               NautilusFileAttributes  file_attributes)
{
    GList *node;

    cancel_loading_attributes (directory, file_attributes);

    for (node = directory->details->file_list; node != NULL; node = node->next)
    {
        nautilus_file_invalidate_attributes_internal (NAUTILUS_FILE (node->data),
                                                      file_attributes);
    }

    if (directory->details->as_file != NULL)
    {
        nautilus_file_invalidate_attributes_internal (directory->details->as_file,
                                                      file_attributes);
    }
}
