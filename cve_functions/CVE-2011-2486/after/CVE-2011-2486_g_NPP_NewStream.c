g_NPP_NewStream(NPP instance, NPMIMEType type, NPStream *stream, NPBool seekable, uint16_t *stype)
{
  if (instance == NULL)
	return NPERR_INVALID_INSTANCE_ERROR;

  if (plugin_funcs.newstream == NULL)
	return NPERR_INVALID_FUNCTABLE_ERROR;

  D(bugiI("NPP_NewStream instance=%p, stream=%p, url='%s', type='%s', seekable=%d, stype=%s, notifyData=%p\n",
		instance, stream, stream->url, type, seekable, string_of_NPStreamType(*stype), stream->notifyData));
  NPError ret = plugin_funcs.newstream(instance, type, stream, seekable, stype);
  D(bugiD("NPP_NewStream return: %d [%s], stype=%s\n", ret, string_of_NPError(ret), string_of_NPStreamType(*stype)));
  return ret;
}
