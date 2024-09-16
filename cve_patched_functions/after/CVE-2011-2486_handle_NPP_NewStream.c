static int handle_NPP_NewStream(rpc_connection_t *connection)
{
  D(bug("handle_NPP_NewStream\n"));

  int error;
  PluginInstance *plugin;
  uint32_t stream_id;
  uint32_t seekable;
  NPMIMEType type;

  NPStream *stream;
  if ((stream = malloc(sizeof(*stream))) == NULL)
	return RPC_ERROR_NO_MEMORY;
  memset(stream, 0, sizeof(*stream));

  error = rpc_method_get_args(connection,
							  RPC_TYPE_NPW_PLUGIN_INSTANCE, &plugin,
							  RPC_TYPE_STRING, &type,
							  RPC_TYPE_UINT32, &stream_id,
							  RPC_TYPE_STRING, &stream->url,
							  RPC_TYPE_UINT32, &stream->end,
							  RPC_TYPE_UINT32, &stream->lastmodified,
							  RPC_TYPE_NP_NOTIFY_DATA, &stream->notifyData,
							  RPC_TYPE_STRING, &stream->headers,
							  RPC_TYPE_BOOLEAN, &seekable,
							  RPC_TYPE_INVALID);

  if (error != RPC_ERROR_NO_ERROR) {
	npw_perror("NPP_NewStream() get args", error);
	return error;
  }

  StreamInstance *stream_ndata;
  if ((stream_ndata = malloc(sizeof(*stream_ndata))) == NULL)
	return RPC_ERROR_NO_MEMORY;
  stream->ndata = stream_ndata;
  memset(stream_ndata, 0, sizeof(*stream_ndata));
  stream_ndata->stream_id = stream_id;
  id_link(stream_id, stream_ndata);
  stream_ndata->stream = stream;
  stream_ndata->is_plugin_stream = 0;

  uint16_t stype = NP_NORMAL;
  NPError ret = g_NPP_NewStream(PLUGIN_INSTANCE_NPP(plugin), type, stream, seekable, &stype);

  if (type)
	free(type);

  return rpc_method_send_reply(connection,
							   RPC_TYPE_INT32, ret,
							   RPC_TYPE_UINT32, (uint32_t)stype,
							   RPC_TYPE_NP_NOTIFY_DATA, stream->notifyData,
							   RPC_TYPE_INVALID);
}
