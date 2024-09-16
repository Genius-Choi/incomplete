flatpak_proxy_client_update_unique_id_policy_from_name (FlatpakProxyClient *client,
                                                        const char         *unique_id,
                                                        const char         *as_name)
{
  flatpak_proxy_client_update_unique_id_policy (client,
                                                unique_id,
                                                flatpak_proxy_get_policy (client->proxy, as_name));
}
