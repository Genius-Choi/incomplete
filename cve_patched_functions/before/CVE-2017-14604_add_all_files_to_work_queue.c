add_all_files_to_work_queue (NautilusDirectory *directory)
{
    GList *node;
    NautilusFile *file;

    for (node = directory->details->file_list; node != NULL; node = node->next)
    {
        file = NAUTILUS_FILE (node->data);

        nautilus_directory_add_file_to_work_queue (directory, file);
    }
}
