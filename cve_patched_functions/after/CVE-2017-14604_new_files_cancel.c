new_files_cancel (NautilusDirectory *directory)
{
    GList *l;
    NewFilesState *state;

    if (directory->details->new_files_in_progress != NULL)
    {
        for (l = directory->details->new_files_in_progress; l != NULL; l = l->next)
        {
            state = l->data;
            g_cancellable_cancel (state->cancellable);
            state->directory = NULL;
        }
        g_list_free (directory->details->new_files_in_progress);
        directory->details->new_files_in_progress = NULL;
    }
}
