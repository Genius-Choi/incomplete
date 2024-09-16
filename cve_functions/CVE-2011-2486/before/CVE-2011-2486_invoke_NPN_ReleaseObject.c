invoke_NPN_ReleaseObject(NPObject *npobj)
{
  npw_return_val_if_fail(rpc_method_invoke_possible(g_rpc_connection),
						 npobj->referenceCount);

  int error = rpc_method_invoke(g_rpc_connection,
								RPC_METHOD_NPN_RELEASE_OBJECT,
								RPC_TYPE_NP_OBJECT, npobj,
								RPC_TYPE_INVALID);

  if (error != RPC_ERROR_NO_ERROR) {
	npw_perror("NPN_ReleaseObject() invoke", error);
	return npobj->referenceCount;
  }

  uint32_t refcount;
  error = rpc_method_wait_for_reply(g_rpc_connection, RPC_TYPE_UINT32, &refcount, RPC_TYPE_INVALID);

  if (error != RPC_ERROR_NO_ERROR) {
	npw_perror("NPN_ReleaseObject() wait for reply", error);
	return npobj->referenceCount;
  }

  return refcount;
}
