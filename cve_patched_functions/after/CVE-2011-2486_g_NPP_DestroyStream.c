g_NPP_DestroyStream(NPP instance, NPStream *stream, NPReason reason)
{
  if (instance == NULL)
	return NPERR_INVALID_INSTANCE_ERROR;

  if (plugin_funcs.destroystream == NULL)
	return NPERR_INVALID_FUNCTABLE_ERROR;

  if (stream == NULL)
	return NPERR_INVALID_PARAM;

  D(bugiI("NPP_DestroyStream instance=%p, stream=%p, reason=%s\n",
		instance, stream, string_of_NPReason(reason)));
  NPError ret = plugin_funcs.destroystream(instance, stream, reason);
  D(bugiD("NPP_DestroyStream return: %d [%s]\n", ret, string_of_NPError(ret)));

  StreamInstance *stream_ndata = stream->ndata;
  if (stream_ndata) {
	id_remove(stream_ndata->stream_id);
	free(stream_ndata);
  }
  free((char *)stream->url);
  free((char *)stream->headers);
  free(stream);

  return ret;
}
