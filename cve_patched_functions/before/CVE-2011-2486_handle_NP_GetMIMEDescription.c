static int handle_NP_GetMIMEDescription(rpc_connection_t *connection)
{
  D(bug("handle_NP_GetMIMEDescription\n"));

  int error = rpc_method_get_args(connection, RPC_TYPE_INVALID);
  if (error != RPC_ERROR_NO_ERROR) {
	npw_perror("NP_GetMIMEDescription() get args", error);
	return error;
  }

  char *str = g_NP_GetMIMEDescription();
  return rpc_method_send_reply(connection, RPC_TYPE_STRING, str, RPC_TYPE_INVALID);
}
