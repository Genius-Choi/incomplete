invoke_NPN_IntFromIdentifier(NPIdentifier identifier)
{
  npw_return_val_if_fail(rpc_method_invoke_possible(g_rpc_connection), -1);

  int error = rpc_method_invoke(g_rpc_connection,
								RPC_METHOD_NPN_INT_FROM_IDENTIFIER,
								RPC_TYPE_NP_IDENTIFIER, &identifier,
								RPC_TYPE_INVALID);

  if (error != RPC_ERROR_NO_ERROR) {
	npw_perror("NPN_IntFromIdentifier() invoke", error);
	return -1;
  }

  int32_t ret;
  error = rpc_method_wait_for_reply(g_rpc_connection,
									RPC_TYPE_INT32, &ret,
									RPC_TYPE_INVALID);

  if (error != RPC_ERROR_NO_ERROR) {
	npw_perror("NPN_IntFromIdentifier() wait for reply", error);
	return -1;
  }

  return ret;
}
