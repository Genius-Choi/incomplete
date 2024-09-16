has_problem (NautilusDirectory *directory,
             NautilusFile      *file,
             FileCheck          problem)
{
    GList *node;

    if (file != NULL)
    {
        return (*problem)(file);
    }

    for (node = directory->details->file_list; node != NULL; node = node->next)
    {
        if ((*problem)(node->data))
        {
            return TRUE;
        }
    }

    return FALSE;
}
