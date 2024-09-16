info_provider_callback (NautilusInfoProvider    *provider,
                        NautilusOperationHandle *handle,
                        NautilusOperationResult  result,
                        gpointer                 user_data)
{
    InfoProviderResponse *response;

    response = g_new0 (InfoProviderResponse, 1);
    response->provider = provider;
    response->handle = handle;
    response->result = result;
    response->directory = NAUTILUS_DIRECTORY (user_data);

    response->directory->details->extension_info_idle =
        g_idle_add_full (G_PRIORITY_DEFAULT_IDLE,
                         info_provider_idle_callback, response,
                         g_free);
}
