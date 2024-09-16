cib_ipc_created(qb_ipcs_connection_t *c)
{
    cib_client_t *cib_client = qb_ipcs_context_get(c);

    crm_trace("%p connected for client %s", c, cib_client->id);
}
