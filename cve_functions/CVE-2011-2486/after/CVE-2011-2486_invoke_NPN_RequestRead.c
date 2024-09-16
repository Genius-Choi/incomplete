invoke_NPN_RequestRead(NPStream *stream, NPByteRange *rangeList)
{
  npw_return_val_if_fail(rpc_method_invoke_possible(g_rpc_connection),
						 NPERR_GENERIC_ERROR);

  int error = rpc_method_invoke(g_rpc_connection,
								RPC_METHOD_NPN_REQUEST_READ,
								RPC_TYPE_NP_STREAM, stream,
								RPC_TYPE_NP_BYTE_RANGE, rangeList,
								RPC_TYPE_INVALID);

  if (error != RPC_ERROR_NO_ERROR) {
	npw_perror("NPN_RequestRead() invoke", error);
	return NPERR_GENERIC_ERROR;
  }

  int32_t ret;
  error = rpc_method_wait_for_reply(g_rpc_connection, RPC_TYPE_INT32, &ret, RPC_TYPE_INVALID);

  if (error != RPC_ERROR_NO_ERROR) {
	npw_perror("NPN_RequestRead() wait for reply", error);
	return NPERR_GENERIC_ERROR;
  }

  return ret;
}
