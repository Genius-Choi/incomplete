static int do_recv_XKeyEvent(rpc_message_t *message, XEvent *xevent)
{
  int32_t x, y, x_root, y_root, same_screen;
  uint32_t root, subwindow, time, state, keycode;
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
  if ((error = rpc_message_recv_uint32(message, &keycode)) < 0)
	return error;
  if ((error = rpc_message_recv_int32(message, &same_screen)) < 0)
	return error;
  xevent->xkey.root = root;
  xevent->xkey.subwindow = subwindow;
  xevent->xkey.time = time;
  xevent->xkey.x = x;
  xevent->xkey.y = y;
  xevent->xkey.x_root = x_root;
  xevent->xkey.y_root = y_root;
  xevent->xkey.state = state;
  xevent->xkey.keycode = keycode;
  xevent->xkey.same_screen = same_screen;
  return RPC_ERROR_NO_ERROR;
}
