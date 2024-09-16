terminate_cib(const char *caller, gboolean fast)
{
    if (remote_fd > 0) {
        close(remote_fd);
        remote_fd = 0;
    }
    if (remote_tls_fd > 0) {
        close(remote_tls_fd);
        remote_tls_fd = 0;
    }
    
    if(!fast) {
        crm_info("%s: Disconnecting from cluster infrastructure", caller);
        crm_cluster_disconnect(&crm_cluster);
    }

    uninitializeCib();

    crm_info("%s: Exiting%s...", caller, fast?" fast":mainloop?" from mainloop":"");

    if(fast == FALSE && mainloop != NULL && g_main_is_running(mainloop)) {
        g_main_quit(mainloop);

    } else {
        qb_ipcs_destroy(ipcs_ro);
        qb_ipcs_destroy(ipcs_rw);
        qb_ipcs_destroy(ipcs_shm);

        if (fast) {
            crm_exit(EX_USAGE);
        } else {
            crm_exit(EX_OK);
        }
    }
}
