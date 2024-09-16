g_NPP_Print(NPP instance, NPPrint *printInfo)
{
  if (plugin_funcs.print == NULL)
	return;

  if (printInfo == NULL)
	return;

  D(bugiI("NPP_Print instance=%p, printInfo->mode=%d\n", instance, printInfo->mode));
  plugin_funcs.print(instance, printInfo);
  D(bugiD("NPP_Print done\n"));
}
