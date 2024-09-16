qb_ipcs_service_t *mainloop_add_ipc_server(
    const char *name, enum qb_ipc_type type, struct qb_ipcs_service_handlers *callbacks) 
{
    int rc = 0;
    qb_ipcs_service_t* server = NULL;

    if(gio_map == NULL) {
        gio_map = qb_array_create_2(64, sizeof(struct gio_to_qb_poll), 1);
    }

    server = qb_ipcs_create(name, 0, pick_ipc_type(type), callbacks);
    qb_ipcs_poll_handlers_set(server, &gio_poll_funcs);

    rc = qb_ipcs_run(server);
    if (rc < 0) {
        crm_err("Could not start %s IPC server: %s (%d)", name, pcmk_strerror(rc), rc);
        return NULL;
    }

    return server;
}
