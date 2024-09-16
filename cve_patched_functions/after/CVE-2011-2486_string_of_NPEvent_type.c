const char *string_of_NPEvent_type(int type)
{
  const char *str;

  switch (type) {
#define _(VAL) case VAL: str = #VAL; break;
#ifdef MOZ_X11
    _(KeyPress);
    _(KeyRelease);
    _(ButtonPress);
    _(ButtonRelease);
    _(MotionNotify);
    _(EnterNotify);
    _(LeaveNotify);
    _(FocusIn);
    _(FocusOut);
    _(KeymapNotify);
    _(Expose);
    _(GraphicsExpose);
    _(NoExpose);
    _(VisibilityNotify);
    _(CreateNotify);
    _(DestroyNotify);
    _(UnmapNotify);
    _(MapNotify);
    _(MapRequest);
    _(ReparentNotify);
    _(ConfigureNotify);
    _(ConfigureRequest);
    _(GravityNotify);
    _(ResizeRequest);
    _(CirculateNotify);
    _(CirculateRequest);
    _(PropertyNotify);
    _(SelectionClear);
    _(SelectionRequest);
    _(SelectionNotify);
    _(ColormapNotify);
    _(ClientMessage);
    _(MappingNotify);
#endif
#undef _
  default:
	str = "<unknown type>";
	break;
  }

  return str;
}
