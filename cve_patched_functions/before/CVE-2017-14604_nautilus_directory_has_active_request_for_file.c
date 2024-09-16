nautilus_directory_has_active_request_for_file (NautilusDirectory *directory,
                                                NautilusFile      *file)
{
    GList *node;
    ReadyCallback *callback;
    Monitor *monitor;

    for (node = directory->details->call_when_ready_list;
         node != NULL; node = node->next)
    {
        callback = node->data;
        if (callback->file == file ||
            callback->file == NULL)
        {
            return TRUE;
        }
    }

    for (node = directory->details->monitor_list;
         node != NULL; node = node->next)
    {
        monitor = node->data;
        if (monitor->file == file ||
            monitor->file == NULL)
        {
            return TRUE;
        }
    }

    return FALSE;
}
