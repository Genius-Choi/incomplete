g_NPP_Write(NPP instance, NPStream *stream, int32_t offset, int32_t len, void *buf)
{
  if (instance == NULL)
	return -1;

  if (plugin_funcs.write == NULL)
	return -1;

  if (stream == NULL)
	return -1;

  D(bugiI("NPP_Write instance=%p, stream=%p, offset=%d, len=%d, buf=%p\n", instance, stream, offset, len, buf));
  int32_t ret = plugin_funcs.write(instance, stream, offset, len, buf);
  D(bugiD("NPP_Write return: %d\n", ret));
  return ret;
}
