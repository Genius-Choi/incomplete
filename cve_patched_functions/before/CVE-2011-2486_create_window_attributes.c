static int create_window_attributes(NPSetWindowCallbackStruct *ws_info)
{
  if (ws_info == NULL)
	return -1;
  GdkVisual *gdk_visual;
  if (ws_info->visual)
	gdk_visual = gdkx_visual_get((uintptr_t)ws_info->visual);
  else
	gdk_visual = gdk_visual_get_system();
  if (gdk_visual == NULL) {
	npw_printf("ERROR: could not reconstruct XVisual from visualID\n");
	return -2;
  }
  ws_info->display = x_display;
  ws_info->visual = gdk_x11_visual_get_xvisual(gdk_visual);
  return 0;
}
