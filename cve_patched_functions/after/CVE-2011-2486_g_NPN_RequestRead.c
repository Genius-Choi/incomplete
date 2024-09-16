g_NPN_RequestRead(NPStream *stream, NPByteRange *rangeList)
{
  if (!thread_check()) {
	npw_printf("WARNING: NPN_RequestRead not called from the main thread\n");
	return NPERR_INVALID_INSTANCE_ERROR;
  }

  if (stream == NULL || stream->ndata == NULL || rangeList == NULL)
	return NPERR_INVALID_PARAM;

  D(bugiI("NPN_RequestRead stream=%p\n", stream));
  NPError ret = invoke_NPN_RequestRead(stream, rangeList);
  D(bugiD("NPN_RequestRead return: %d [%s]\n", ret, string_of_NPError(ret)));
  return ret;
}
