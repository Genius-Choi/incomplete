void mainloop_del_ipc_server(qb_ipcs_service_t *server) 
{
    if(server) {
        qb_ipcs_destroy(server);
    }
}
