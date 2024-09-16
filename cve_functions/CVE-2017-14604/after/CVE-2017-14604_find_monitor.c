find_monitor (NautilusDirectory *directory,
              NautilusFile      *file,
              gconstpointer      client)
{
    Monitor monitor;

    monitor.client = client;
    monitor.file = file;

    return g_list_find_custom (directory->details->monitor_list,
                               &monitor,
                               monitor_key_compare);
}
