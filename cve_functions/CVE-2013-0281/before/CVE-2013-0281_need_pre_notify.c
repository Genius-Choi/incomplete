need_pre_notify(gpointer key, gpointer value, gpointer user_data)
{
    cib_client_t *client = value;

    if (client->pre_notify) {
        gboolean *needed = user_data;

        *needed = TRUE;
    }
}
