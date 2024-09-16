static int untrap_errors(void)
{
  XSetErrorHandler(old_error_handler);
  return trapped_error_code;
}
