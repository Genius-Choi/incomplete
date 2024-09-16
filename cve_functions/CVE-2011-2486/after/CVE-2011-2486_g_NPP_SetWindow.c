g_NPP_SetWindow(NPP instance, NPWindow *np_window)
{
  if (instance == NULL)
	return NPERR_INVALID_INSTANCE_ERROR;

  PluginInstance *plugin = PLUGIN_INSTANCE(instance);
  if (plugin == NULL)
	return NPERR_INVALID_INSTANCE_ERROR;

  if (plugin_funcs.setwindow == NULL)
	return NPERR_INVALID_FUNCTABLE_ERROR;

  plugin->is_windowless = np_window && np_window->type == NPWindowTypeDrawable;

  NPWindow *window = np_window;
  if (window && (window->window || plugin->is_windowless)) {
	if (plugin->toolkit_data) {
	  if (update_window(plugin, window) < 0)
		return NPERR_GENERIC_ERROR;
	}
	else {
	  if (create_window(plugin, window) < 0)
		return NPERR_GENERIC_ERROR;
	}
	window = &plugin->window;
  }

  D(bugiI("NPP_SetWindow instance=%p, window=%p\n", instance, window ? window->window : NULL));
  NPError ret = plugin_funcs.setwindow(instance, window);
  D(bugiD("NPP_SetWindow return: %d [%s]\n", ret, string_of_NPError(ret)));

  if (np_window == NULL || (np_window->window == NULL && !plugin->is_windowless))
	destroy_window(plugin);

  return ret;
}
