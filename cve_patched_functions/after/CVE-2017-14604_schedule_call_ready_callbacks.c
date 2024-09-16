schedule_call_ready_callbacks (NautilusDirectory *directory)
{
    if (directory->details->call_ready_idle_id == 0)
    {
        directory->details->call_ready_idle_id
            = g_idle_add (call_ready_callbacks_at_idle, directory);
    }
}
