queue_local_notify(xmlNode * notify_src, const char *client_id, gboolean sync_reply, gboolean from_peer)
{
    cib_local_notify_t *notify = calloc(1, sizeof(cib_local_notify_t));

    notify->notify_src = notify_src;
    notify->client_id = strdup(client_id);
    notify->sync_reply = sync_reply;
    notify->from_peer = from_peer;

    if (!local_notify_queue) {
        local_notify_queue = g_hash_table_new_full(g_direct_hash,
            g_direct_equal, NULL, local_notify_destroy_callback);
    }

    g_hash_table_insert(local_notify_queue, GINT_TO_POINTER(cib_local_bcast_num), notify);
}
