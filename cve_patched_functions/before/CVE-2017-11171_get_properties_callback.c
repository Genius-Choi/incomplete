get_properties_callback (SmsConn   conn,
                         SmPointer manager_data)
{
        GsmXSMPClient *client = manager_data;

        g_debug ("GsmXSMPClient: Get properties request from '%s'", client->priv->description);

        SmsReturnProperties (conn,
                             client->priv->props->len,
                             (SmProp **)client->priv->props->pdata);
}
