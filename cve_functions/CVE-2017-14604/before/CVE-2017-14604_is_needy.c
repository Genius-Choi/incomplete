is_needy (NautilusFile *file,
          FileCheck     check_missing,
          RequestType   request_type_wanted)
{
    NautilusDirectory *directory;
    GList *node;
    ReadyCallback *callback;
    Monitor *monitor;

    if (!(*check_missing)(file))
    {
        return FALSE;
    }

    directory = file->details->directory;
    if (directory->details->call_when_ready_counters[request_type_wanted] > 0)
    {
        for (node = directory->details->call_when_ready_list;
             node != NULL; node = node->next)
        {
            callback = node->data;
            if (callback->active &&
                REQUEST_WANTS_TYPE (callback->request, request_type_wanted))
            {
                if (callback->file == file)
                {
                    return TRUE;
                }
                if (callback->file == NULL
                    && file != directory->details->as_file)
                {
                    return TRUE;
                }
            }
        }
    }

    if (directory->details->monitor_counters[request_type_wanted] > 0)
    {
        for (node = directory->details->monitor_list;
             node != NULL; node = node->next)
        {
            monitor = node->data;
            if (REQUEST_WANTS_TYPE (monitor->request, request_type_wanted))
            {
                if (monitor_includes_file (monitor, file))
                {
                    return TRUE;
                }
            }
        }
    }
    return FALSE;
}
