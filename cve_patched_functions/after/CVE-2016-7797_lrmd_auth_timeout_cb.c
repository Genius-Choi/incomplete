lrmd_auth_timeout_cb(gpointer data)
{
    crm_client_t *client = data;

    client->remote->auth_timeout = 0;

    if (client->remote->tls_handshake_complete == TRUE) {
        return FALSE;
    }

    mainloop_del_fd(client->remote->source);
    client->remote->source = NULL;
    crm_err("Remote client authentication timed out");

    return FALSE;
}
