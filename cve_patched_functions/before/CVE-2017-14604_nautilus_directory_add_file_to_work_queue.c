nautilus_directory_add_file_to_work_queue (NautilusDirectory *directory,
                                           NautilusFile      *file)
{
    g_return_if_fail (file->details->directory == directory);

    nautilus_file_queue_enqueue (directory->details->high_priority_queue,
                                 file);
}
