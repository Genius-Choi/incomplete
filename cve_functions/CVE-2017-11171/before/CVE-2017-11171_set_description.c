set_description (GsmXSMPClient *client)
{
        SmProp     *prop;
        const char *id;

        prop = find_property (client, SmProgram, NULL);
        id = gsm_client_peek_startup_id (GSM_CLIENT (client));

        g_free (client->priv->description);
        if (prop) {
                client->priv->description = g_strdup_printf ("%p [%.*s %s]",
                                                             client,
                                                             prop->vals[0].length,
                                                             (char *)prop->vals[0].value,
                                                             id);
        } else if (id != NULL) {
                client->priv->description = g_strdup_printf ("%p [%s]", client, id);
        } else {
                client->priv->description = g_strdup_printf ("%p", client);
        }
}
