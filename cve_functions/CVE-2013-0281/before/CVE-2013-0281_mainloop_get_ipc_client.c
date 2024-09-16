mainloop_get_ipc_client(mainloop_io_t *client)
{
    if(client) {
        return client->ipc;
    }
    return NULL;
}
