invoke_NPN_SetException(NPObject *npobj, const NPUTF8 *message)
{
  npw_return_if_fail(rpc_method_invoke_possible(g_rpc_connection));

  int error = rpc_method_invoke(g_rpc_connection,
								RPC_METHOD_NPN_SET_EXCEPTION,
								RPC_TYPE_NP_OBJECT, npobj,
								RPC_TYPE_STRING, message,
								RPC_TYPE_INVALID);

  if (error != RPC_ERROR_NO_ERROR) {
	npw_perror("NPN_SetException() invoke", error);
	return;
  }

  error = rpc_method_wait_for_reply(g_rpc_connection, RPC_TYPE_INVALID);

  if (error != RPC_ERROR_NO_ERROR) {
	npw_perror("NPN_SetException() wait for reply", error);
	return;
  }
}
