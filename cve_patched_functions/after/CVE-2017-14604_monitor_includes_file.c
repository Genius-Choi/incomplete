monitor_includes_file (const Monitor *monitor,
                       NautilusFile  *file)
{
    if (monitor->file == file)
    {
        return TRUE;
    }
    if (monitor->file != NULL)
    {
        return FALSE;
    }
    if (file == file->details->directory->details->as_file)
    {
        return FALSE;
    }
    return nautilus_file_should_show (file,
                                      monitor->monitor_hidden_files,
                                      TRUE);
}
