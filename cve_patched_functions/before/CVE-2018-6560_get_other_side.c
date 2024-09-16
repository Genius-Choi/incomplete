get_other_side (ProxySide *side)
{
  FlatpakProxyClient *client = side->client;

  if (side == &client->client_side)
    return &client->bus_side;

  return &client->client_side;
}
