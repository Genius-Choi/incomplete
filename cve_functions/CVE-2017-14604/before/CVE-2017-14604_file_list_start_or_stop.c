file_list_start_or_stop (NautilusDirectory *directory)
{
    if (nautilus_directory_is_anyone_monitoring_file_list (directory))
    {
        start_monitoring_file_list (directory);
    }
    else
    {
        nautilus_directory_stop_monitoring_file_list (directory);
    }
}
