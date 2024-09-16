fep_client_set_event_filter (FepClient *client,
			     FepEventFilter filter,
			     void *data)
{
  client->filter = filter;
  client->filter_data = data;
}
