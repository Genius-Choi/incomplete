static int do_recv_XMotionEvent(rpc_message_t *message, XEvent *xevent)
{
  char is_hint;
  int32_t x, y, x_root, y_root, same_screen;
  uint32_t root, subwindow, time, state;
  int error;
  if ((error = do_recv_XAnyEvent(message, xevent)) < 0)
	return error;
  if ((error = rpc_message_recv_uint32(message, &root)) < 0)
	return error;
  if ((error = rpc_message_recv_uint32(message, &subwindow)) < 0)
	return error;
  if ((error = rpc_message_recv_uint32(message, &time)) < 0)
	return error;
  if ((error = rpc_message_recv_int32(message, &x)) < 0)
	return error;
  if ((error = rpc_message_recv_int32(message, &y)) < 0)
	return error;
  if ((error = rpc_message_recv_int32(message, &x_root)) < 0)
	return error;
  if ((error = rpc_message_recv_int32(message, &y_root)) < 0)
	return error;
  if ((error = rpc_message_recv_uint32(message, &state)) < 0)
	return error;
  if ((error = rpc_message_recv_char(message, &is_hint)) < 0)
	return error;
  if ((error = rpc_message_recv_int32(message, &same_screen)) < 0)
	return error;
  xevent->xmotion.root = root;
  xevent->xmotion.subwindow = subwindow;
  xevent->xmotion.time = time;
  xevent->xmotion.x = x;
  xevent->xmotion.y = y;
  xevent->xmotion.x_root = x_root;
  xevent->xmotion.y_root = y_root;
  xevent->xmotion.state = state;
  xevent->xmotion.is_hint = is_hint;
  xevent->xmotion.same_screen = same_screen;
  return RPC_ERROR_NO_ERROR;
}
