static void rpc_error_callback_cb(rpc_connection_t *connection, void *user_data)
{
  D(bug("RPC connection %p is in a bad state, closing the plugin\n",connection));
  rpc_connection_set_error_callback(connection, NULL, NULL);
  gtk_main_quit();
}
