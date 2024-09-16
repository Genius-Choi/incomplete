static inline int add_appcontext_input(int fd, int n)
{
  return XtAppAddInput(x_app_context,
					   fd,
					   GUINT_TO_POINTER(XtInputWriteMask),
					   xt_dummy_input_cb,
					   GUINT_TO_POINTER(0xdead0000));
}
