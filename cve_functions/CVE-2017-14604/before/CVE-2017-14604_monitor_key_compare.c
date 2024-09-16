monitor_key_compare (gconstpointer a,
                     gconstpointer data)
{
    const Monitor *monitor;
    const Monitor *compare_monitor;

    monitor = a;
    compare_monitor = data;

    if (monitor->client < compare_monitor->client)
    {
        return -1;
    }
    if (monitor->client > compare_monitor->client)
    {
        return +1;
    }

    if (monitor->file < compare_monitor->file)
    {
        return -1;
    }
    if (monitor->file > compare_monitor->file)
    {
        return +1;
    }

    return 0;
}
