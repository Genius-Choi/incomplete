mainloop_del_ipc_client(mainloop_io_t *client)
{
    mainloop_del_fd(client);
}
