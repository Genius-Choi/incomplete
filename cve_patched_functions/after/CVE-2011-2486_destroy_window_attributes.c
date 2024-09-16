static void destroy_window_attributes(NPSetWindowCallbackStruct *ws_info)
{
  if (ws_info == NULL)
	return;
  NPW_MemFree(ws_info);
}
