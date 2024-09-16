g_NPP_URLNotify(NPP instance, const char *url, NPReason reason, void *notifyData)
{
  if (instance == NULL)
	return;

  if (plugin_funcs.urlnotify == NULL)
	return;

  D(bugiI("NPP_URLNotify instance=%p, url='%s', reason=%s, notifyData=%p\n",
		instance, url, string_of_NPReason(reason), notifyData));
  plugin_funcs.urlnotify(instance, url, reason, notifyData);
  D(bugiD("NPP_URLNotify done\n"));
}
