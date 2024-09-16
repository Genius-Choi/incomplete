invoke_NPN_GetStringIdentifiers(const NPUTF8 **names, int32_t nameCount, NPIdentifier *identifiers)
{
  npw_return_if_fail(rpc_method_invoke_possible(g_rpc_connection));

  int error = rpc_method_invoke(g_rpc_connection,
								RPC_METHOD_NPN_GET_STRING_IDENTIFIERS,
								RPC_TYPE_ARRAY, RPC_TYPE_STRING, nameCount, names,
								RPC_TYPE_INVALID);

  if (error != RPC_ERROR_NO_ERROR) {
	npw_perror("NPN_GetStringIdentifiers() invoke", error);
	return;
  }

  uint32_t n_idents;
  NPIdentifier *idents;
  error = rpc_method_wait_for_reply(g_rpc_connection,
									RPC_TYPE_ARRAY, RPC_TYPE_NP_IDENTIFIER, &n_idents, &idents,
									RPC_TYPE_INVALID);

  if (error != RPC_ERROR_NO_ERROR) {
	npw_perror("NPN_GetStringIdentifiers() wait for reply", error);
	return;
  }

  if (identifiers) {
	if (n_idents != nameCount) {
	  npw_printf("ERROR: NPN_GetStringIdentifiers returned fewer NPIdentifiers than expected\n");
	  if (n_idents > nameCount)
		n_idents = nameCount;
	}
	for (int i = 0; i < n_idents; i++)
	  identifiers[i] = idents[i];
	free(idents);
  }
}
