remove_monitor (NautilusDirectory *directory,
                NautilusFile      *file,
                gconstpointer      client)
{
    remove_monitor_link (directory, find_monitor (directory, file, client));
}
