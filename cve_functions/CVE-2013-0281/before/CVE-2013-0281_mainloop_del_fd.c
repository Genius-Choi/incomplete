mainloop_del_fd(mainloop_io_t *client)
{
    if(client != NULL) {
        crm_trace("Removing client %s[%p] %d", client->name, client, mainloop_gio_refcount(client));
        if (client->source) {
            /* Results in mainloop_gio_destroy() being called just
             * before the source is removed from mainloop
             */
            g_source_remove(client->source);
        }
    }
}
