file_list_cancel (NautilusDirectory *directory)
{
    directory_load_cancel (directory);

    if (directory->details->dequeue_pending_idle_id != 0)
    {
        g_source_remove (directory->details->dequeue_pending_idle_id);
        directory->details->dequeue_pending_idle_id = 0;
    }

    if (directory->details->pending_file_info != NULL)
    {
        g_list_free_full (directory->details->pending_file_info, g_object_unref);
        directory->details->pending_file_info = NULL;
    }
}
