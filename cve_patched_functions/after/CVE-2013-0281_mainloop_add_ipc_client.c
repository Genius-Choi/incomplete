mainloop_add_ipc_client(
    const char *name, int priority, size_t max_size, void *userdata, struct ipc_client_callbacks *callbacks) 
{
    mainloop_io_t *client = NULL;
    crm_ipc_t *conn = crm_ipc_new(name, max_size);

    if(conn && crm_ipc_connect(conn)) {
        int32_t fd = crm_ipc_get_fd(conn);
        client = mainloop_add_fd(name, priority, fd, userdata, NULL);
        client->ipc = conn;
        client->destroy_fn = callbacks->destroy;
        client->dispatch_fn_ipc = callbacks->dispatch;
    }

    if(conn && client == NULL) {
        crm_trace("Connection to %s failed", name);
        crm_ipc_close(conn);
        crm_ipc_destroy(conn);
    }
    
    return client;
}
