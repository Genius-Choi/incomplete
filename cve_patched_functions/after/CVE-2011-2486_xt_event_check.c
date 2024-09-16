static gboolean xt_event_check(GSource *source)
{
  if (xt_event_poll_fd.revents & G_IO_IN) {
	int mask = XtAppPending(x_app_context);
	if (mask)
	  return TRUE;
  }
  return FALSE;
}
