nautilus_directory_schedule_dequeue_pending (NautilusDirectory *directory)
{
    if (directory->details->dequeue_pending_idle_id == 0)
    {
        directory->details->dequeue_pending_idle_id
            = g_idle_add (dequeue_pending_idle_callback, directory);
    }
}
