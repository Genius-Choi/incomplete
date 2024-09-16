remove_callback_link_keep_data (NautilusDirectory *directory,
                                GList             *link)
{
    ReadyCallback *callback;

    callback = link->data;

    directory->details->call_when_ready_list = g_list_remove_link
                                                   (directory->details->call_when_ready_list, link);

    request_counter_remove_request (directory->details->call_when_ready_counters,
                                    callback->request);
    g_list_free_1 (link);
}
