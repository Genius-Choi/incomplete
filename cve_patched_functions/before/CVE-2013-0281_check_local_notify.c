check_local_notify(int bcast_id)
{
    cib_local_notify_t *notify = NULL;

    if (!local_notify_queue) {
        return;
    }

    notify = g_hash_table_lookup(local_notify_queue, GINT_TO_POINTER(bcast_id));

    if (notify) {
        do_local_notify(notify->notify_src, notify->client_id, notify->sync_reply, notify->from_peer);
        g_hash_table_remove(local_notify_queue, GINT_TO_POINTER(bcast_id));
    }
}
