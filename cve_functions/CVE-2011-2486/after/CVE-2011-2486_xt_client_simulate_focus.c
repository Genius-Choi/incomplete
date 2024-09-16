static void xt_client_simulate_focus(Widget w, int type)
{
  XEvent xevent;
  memset(&xevent, 0, sizeof(xevent));
  xevent.xfocus.type = type;
  xevent.xfocus.window = XtWindow(w);
  xevent.xfocus.display = XtDisplay(w);
  xevent.xfocus.mode = NotifyNormal;
  xevent.xfocus.detail = NotifyAncestor;

  trap_errors();
  XSendEvent(XtDisplay(w), xevent.xfocus.window, False, NoEventMask, &xevent);
  XSync(XtDisplay(w), False);
  untrap_errors();
}
