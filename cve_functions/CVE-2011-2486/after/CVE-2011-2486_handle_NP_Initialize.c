static int handle_NP_Initialize(rpc_connection_t *connection)
{
  D(bug("handle_NP_Initialize\n"));

  uint32_t version;
  int error = rpc_method_get_args(connection,
								  RPC_TYPE_UINT32, &version,
								  RPC_TYPE_INVALID);

  if (error != RPC_ERROR_NO_ERROR) {
	npw_perror("NP_Initialize() get args", error);
	return error;
  }

  NPError ret = g_NP_Initialize(version);
  return rpc_method_send_reply(connection, RPC_TYPE_INT32, ret, RPC_TYPE_INVALID);
}
