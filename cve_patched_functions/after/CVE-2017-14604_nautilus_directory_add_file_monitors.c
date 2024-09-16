nautilus_directory_add_file_monitors (NautilusDirectory *directory,
                                      NautilusFile      *file,
                                      FileMonitors      *monitors)
{
    GList **list;
    GList *l;
    Monitor *monitor;

    g_assert (NAUTILUS_IS_DIRECTORY (directory));
    g_assert (NAUTILUS_IS_FILE (file));
    g_assert (file->details->directory == directory);

    if (monitors == NULL)
    {
        return;
    }

    for (l = (GList *) monitors; l != NULL; l = l->next)
    {
        monitor = l->data;
        request_counter_add_request (directory->details->monitor_counters,
                                     monitor->request);
    }

    list = &directory->details->monitor_list;
    *list = g_list_concat (*list, (GList *) monitors);

    nautilus_directory_add_file_to_work_queue (directory, file);

    nautilus_directory_async_state_changed (directory);
}
