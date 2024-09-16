g_NPP_StreamAsFile(NPP instance, NPStream *stream, const char *fname)
{
  if (instance == NULL)
	return;

  if (plugin_funcs.asfile == NULL)
	return;

  if (stream == NULL)
	return;

  D(bugiI("NPP_StreamAsFile instance=%p, stream=%p, fname='%s'\n", instance, stream, fname));
  plugin_funcs.asfile(instance, stream, fname);
  D(bugiD("NPP_StreamAsFile done\n"));
}
