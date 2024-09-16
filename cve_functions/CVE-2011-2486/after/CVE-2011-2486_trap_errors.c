static void trap_errors(void)
{
  trapped_error_code = 0;
  old_error_handler = XSetErrorHandler(error_handler);
}
