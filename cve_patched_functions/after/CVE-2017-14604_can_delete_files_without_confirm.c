can_delete_files_without_confirm (GList *files)
{
    g_assert (files != NULL);

    while (files != NULL)
    {
        if (!can_delete_without_confirm (files->data))
        {
            return FALSE;
        }

        files = files->next;
    }

    return TRUE;
}
