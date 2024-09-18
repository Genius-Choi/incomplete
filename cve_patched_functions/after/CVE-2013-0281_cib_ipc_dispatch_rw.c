cib_ipc_dispatch_rw(qb_ipcs_connection_t *c, void *data, size_t size)
{
    cib_client_t *cib_client = qb_ipcs_context_get(c);
    crm_trace("%p message from %s", c, cib_client->id);
    return cib_common_callback(c, data, size, TRUE);
}
