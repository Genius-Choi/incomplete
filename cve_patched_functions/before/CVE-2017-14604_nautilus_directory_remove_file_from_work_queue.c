nautilus_directory_remove_file_from_work_queue (NautilusDirectory *directory,
                                                NautilusFile      *file)
{
    nautilus_file_queue_remove (directory->details->high_priority_queue,
                                file);
    nautilus_file_queue_remove (directory->details->low_priority_queue,
                                file);
    nautilus_file_queue_remove (directory->details->extension_queue,
                                file);
}
