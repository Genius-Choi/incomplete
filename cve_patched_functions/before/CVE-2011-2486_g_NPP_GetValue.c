g_NPP_GetValue(NPP instance, NPPVariable variable, void *value)
{
  if (instance == NULL)
	return NPERR_INVALID_INSTANCE_ERROR;

  if (plugin_funcs.getvalue == NULL)
	return NPERR_INVALID_FUNCTABLE_ERROR;

  D(bugiI("NPP_GetValue instance=%p, variable=%d [%s]\n", instance, variable, string_of_NPPVariable(variable)));
  NPError ret = plugin_funcs.getvalue(instance, variable, value);
  D(bugiD("NPP_GetValue return: %d [%s]\n", ret, string_of_NPError(ret)));
  return ret;
}
