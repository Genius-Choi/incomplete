fep_client_close (FepClient *client)
{
  close (client->control);
  free (client);
}
