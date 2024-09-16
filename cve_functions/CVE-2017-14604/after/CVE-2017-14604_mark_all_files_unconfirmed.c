mark_all_files_unconfirmed (NautilusDirectory *directory)
{
    GList *node;
    NautilusFile *file;

    for (node = directory->details->file_list; node != NULL; node = node->next)
    {
        file = node->data;
        set_file_unconfirmed (file, TRUE);
    }
}
