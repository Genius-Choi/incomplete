static int handle_NPP_StreamAsFile(rpc_connection_t *connection)
{
  D(bug("handle_NPP_StreamAsFile\n"));

  PluginInstance *plugin;
  NPStream *stream;
  char *fname;
  int error = rpc_method_get_args(connection,
								  RPC_TYPE_NPW_PLUGIN_INSTANCE, &plugin,
								  RPC_TYPE_NP_STREAM, &stream,
								  RPC_TYPE_STRING, &fname,
								  RPC_TYPE_INVALID);

  if (error != RPC_ERROR_NO_ERROR) {
	npw_perror("NPP_StreamAsFile() get args", error);
	return error;
  }

  g_NPP_StreamAsFile(PLUGIN_INSTANCE_NPP(plugin), stream, fname);

  if (fname)
	free(fname);

  return rpc_method_send_reply (connection, RPC_TYPE_INVALID);
}
