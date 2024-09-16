static int do_recv_XCrossingEvent(rpc_message_t *message, XEvent *xevent)
{
  int32_t x, y, x_root, y_root, mode, detail, same_screen, focus;
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
  if ((error = rpc_message_recv_int32(message, &mode)) < 0)
	return error;
  if ((error = rpc_message_recv_int32(message, &detail)) < 0)
	return error;
  if ((error = rpc_message_recv_int32(message, &same_screen)) < 0)
	return error;
  if ((error = rpc_message_recv_int32(message, &focus)) < 0)
	return error;
  if ((error = rpc_message_recv_uint32(message, &state)) < 0)
	return error;
  xevent->xcrossing.root = root;
  xevent->xcrossing.subwindow = subwindow;
  xevent->xcrossing.time = time;
  xevent->xcrossing.x = x;
  xevent->xcrossing.y = y;
  xevent->xcrossing.x_root = x_root;
  xevent->xcrossing.y_root = y_root;
  xevent->xcrossing.mode = mode;
  xevent->xcrossing.detail = detail;
  xevent->xcrossing.same_screen = same_screen;
  xevent->xcrossing.focus = focus;
  xevent->xcrossing.state = state;
  return RPC_ERROR_NO_ERROR;
}
