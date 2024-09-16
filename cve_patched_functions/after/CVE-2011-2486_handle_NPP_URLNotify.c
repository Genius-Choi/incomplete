static int handle_NPP_URLNotify(rpc_connection_t *connection)
{
  D(bug("handle_NPP_URLNotify\n"));

  int error;
  PluginInstance *plugin;
  char *url;
  int32_t reason;
  void *notifyData;

  error = rpc_method_get_args(connection,
							  RPC_TYPE_NPW_PLUGIN_INSTANCE, &plugin,
							  RPC_TYPE_STRING, &url,
							  RPC_TYPE_INT32, &reason,
							  RPC_TYPE_NP_NOTIFY_DATA, &notifyData,
							  RPC_TYPE_INVALID);

  if (error != RPC_ERROR_NO_ERROR) {
	npw_perror("NPP_URLNotify() get args", error);
	return error;
  }

  g_NPP_URLNotify(PLUGIN_INSTANCE_NPP(plugin), url, reason, notifyData);

  if (url)
	free(url);

  return rpc_method_send_reply (connection, RPC_TYPE_INVALID);
}
