invoke_NPN_NewStream(PluginInstance *plugin, NPMIMEType type, const char *target, NPStream **pstream)
{
  npw_return_val_if_fail(rpc_method_invoke_possible(g_rpc_connection),
						 NPERR_GENERIC_ERROR);

  int error = rpc_method_invoke(g_rpc_connection,
								RPC_METHOD_NPN_NEW_STREAM,
								RPC_TYPE_NPW_PLUGIN_INSTANCE, plugin,
								RPC_TYPE_STRING, type,
								RPC_TYPE_STRING, target,
								RPC_TYPE_INVALID);

  if (error != RPC_ERROR_NO_ERROR) {
	npw_perror("NPN_NewStream() invoke", error);
	return NPERR_OUT_OF_MEMORY_ERROR;
  }

  int32_t ret;
  uint32_t stream_id;
  char *url;
  uint32_t end;
  uint32_t lastmodified;
  void *notifyData;
  char *headers;
  error = rpc_method_wait_for_reply(g_rpc_connection,
									RPC_TYPE_INT32, &ret,
									RPC_TYPE_UINT32, &stream_id,
									RPC_TYPE_STRING, &url,
									RPC_TYPE_UINT32, &end,
									RPC_TYPE_UINT32, &lastmodified,
									RPC_TYPE_NP_NOTIFY_DATA, &notifyData,
									RPC_TYPE_STRING, &headers,
									RPC_TYPE_INVALID);

  if (error != RPC_ERROR_NO_ERROR) {
	npw_perror("NPN_NewStream() wait for reply", error);
	return NPERR_GENERIC_ERROR;
  }

  NPStream *stream = NULL;
  if (ret == NPERR_NO_ERROR) {
	if ((stream = malloc(sizeof(*stream))) == NULL)
	  return NPERR_OUT_OF_MEMORY_ERROR;
	memset(stream, 0, sizeof(*stream));

	StreamInstance *stream_ndata;
	if ((stream_ndata = malloc(sizeof(*stream_ndata))) == NULL) {
	  free(stream);
	  return NPERR_OUT_OF_MEMORY_ERROR;
	}
	stream->ndata = stream_ndata;
	stream->url = url;
	stream->end = end;
	stream->lastmodified = lastmodified;
	stream->notifyData = notifyData;
	stream->headers = headers;
	memset(stream_ndata, 0, sizeof(*stream_ndata));
	stream_ndata->stream_id = stream_id;
	id_link(stream_id, stream_ndata);
	stream_ndata->stream = stream;
	stream_ndata->is_plugin_stream = 1;
  }
  else {
	if (url)
	  free(url);
	if (headers)
	  free(headers);
  }
  *pstream = stream;

  return ret;
}
