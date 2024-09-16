cib_client_status_callback(const char *node, const char *client, const char *status, void *private)
{
    crm_node_t *peer = NULL;

    if (safe_str_eq(client, CRM_SYSTEM_CIB)) {
        crm_info("Status update: Client %s/%s now has status [%s]", node, client, status);

        if (safe_str_eq(status, JOINSTATUS)) {
            status = ONLINESTATUS;

        } else if (safe_str_eq(status, LEAVESTATUS)) {
            status = OFFLINESTATUS;
        }

        peer = crm_get_peer(0, node);
        crm_update_peer_proc(__FUNCTION__, peer, crm_proc_cib, status);
    }
    return;
}
