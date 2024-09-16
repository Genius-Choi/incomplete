cib_ipc_closed(qb_ipcs_connection_t *c) 
{
    cib_client_t *cib_client = qb_ipcs_context_get(c);
    crm_trace("Connection %p closed", c);

    CRM_ASSERT(cib_client != NULL);
    CRM_ASSERT(cib_client->id != NULL);

    if (!g_hash_table_remove(client_list, cib_client->id)) {
        crm_err("Client %s not found in the hashtable", cib_client->name);
    }

    return 0;
}
