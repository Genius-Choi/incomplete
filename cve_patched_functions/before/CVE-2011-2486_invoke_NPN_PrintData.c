invoke_NPN_PrintData(PluginInstance *plugin, uint32_t platform_print_id, NPPrintData *printData)
{
  if (printData == NULL)
	return;

  npw_return_if_fail(rpc_method_invoke_possible(g_rpc_connection));

  int error = rpc_method_invoke(g_rpc_connection,
								RPC_METHOD_NPN_PRINT_DATA,
								RPC_TYPE_UINT32, platform_print_id,
								RPC_TYPE_NP_PRINT_DATA, printData,
								RPC_TYPE_INVALID);

  if (error != RPC_ERROR_NO_ERROR) {
	npw_perror("NPN_PrintData() invoke", error);
	return;
  }

  error = rpc_method_wait_for_reply(g_rpc_connection, RPC_TYPE_INVALID);

  if (error != RPC_ERROR_NO_ERROR) {
	npw_perror("NPN_PrintData() wait for reply", error);
	return;
  }
}
