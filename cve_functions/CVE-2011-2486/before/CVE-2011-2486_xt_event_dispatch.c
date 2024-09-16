static gboolean xt_event_dispatch(GSource *source, GSourceFunc callback, gpointer user_data)
{
  int i;
  for (i = 0; i < XT_MAX_DISPATCH_EVENTS; i++) {
	int mask = XtAppPending(x_app_context);
	if (mask == 0)
	  break;
	XtAppProcessEvent(x_app_context, XtIMAll);
  }
  return TRUE;
}
