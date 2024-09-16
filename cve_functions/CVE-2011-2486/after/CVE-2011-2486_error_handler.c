static int error_handler(Display *display, XErrorEvent *error)
{
  trapped_error_code = error->error_code;
  return 0;
}
