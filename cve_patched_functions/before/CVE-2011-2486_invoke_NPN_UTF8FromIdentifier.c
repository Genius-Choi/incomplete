invoke_NPN_UTF8FromIdentifier(NPIdentifier identifier)
{
  npw_return_val_if_fail(rpc_method_invoke_possible(g_rpc_connection), NULL);

  int error = rpc_method_invoke(g_rpc_connection,
								RPC_METHOD_NPN_UTF8_FROM_IDENTIFIER,
								RPC_TYPE_NP_IDENTIFIER, &identifier,
								RPC_TYPE_INVALID);

  if (error != RPC_ERROR_NO_ERROR) {
	npw_perror("NPN_UTF8FromIdentifier() invoke", error);
	return NULL;
  }

  NPUTF8 *str;
  error = rpc_method_wait_for_reply(g_rpc_connection,
									RPC_TYPE_NP_UTF8, &str,
									RPC_TYPE_INVALID);

  if (error != RPC_ERROR_NO_ERROR) {
	npw_perror("NPN_UTF8FromIdentifier() wait for reply", error);
	return NULL;
  }

  return str;
}
