remove_monitor_link (NautilusDirectory *directory,
                     GList             *link)
{
    Monitor *monitor;

    if (link != NULL)
    {
        monitor = link->data;
        request_counter_remove_request (directory->details->monitor_counters,
                                        monitor->request);
        directory->details->monitor_list =
            g_list_remove_link (directory->details->monitor_list, link);
        g_free (monitor);
        g_list_free_1 (link);
    }
}
