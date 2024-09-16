invoke_NPN_UserAgent(void)
{
  npw_return_val_if_fail(rpc_method_invoke_possible(g_rpc_connection), NULL);

  int error = rpc_method_invoke(g_rpc_connection,
								RPC_METHOD_NPN_USER_AGENT,
								RPC_TYPE_INVALID);

  if (error != RPC_ERROR_NO_ERROR) {
	npw_perror("NPN_UserAgent() invoke", error);
	return NULL;
  }

  char *user_agent;
  error = rpc_method_wait_for_reply(g_rpc_connection,
									RPC_TYPE_STRING, &user_agent,
									RPC_TYPE_INVALID);

  if (error != RPC_ERROR_NO_ERROR) {
	npw_perror("NPN_UserAgent() wait for reply", error);
	return NULL;
  }

  return user_agent;
}
