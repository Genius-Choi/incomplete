static int do_send_XKeyEvent(rpc_message_t *message, XEvent *xevent)
{
  int error;
  if ((error = do_send_XAnyEvent(message, xevent)) < 0)
	return error;
  if ((error = rpc_message_send_uint32(message, xevent->xkey.root)) < 0)
	return error;
  if ((error = rpc_message_send_uint32(message, xevent->xkey.subwindow)) < 0)
	return error;
  if ((error = rpc_message_send_uint32(message, xevent->xkey.time)) < 0)
	return error;
  if ((error = rpc_message_send_int32(message, xevent->xkey.x)) < 0)
	return error;
  if ((error = rpc_message_send_int32(message, xevent->xkey.y)) < 0)
	return error;
  if ((error = rpc_message_send_int32(message, xevent->xkey.x_root)) < 0)
	return error;
  if ((error = rpc_message_send_int32(message, xevent->xkey.y_root)) < 0)
	return error;
  if ((error = rpc_message_send_uint32(message, xevent->xkey.state)) < 0)
	return error;
  if ((error = rpc_message_send_uint32(message, xevent->xkey.keycode)) < 0)
	return error;
  if ((error = rpc_message_send_int32(message, xevent->xkey.same_screen)) < 0)
	return error;
  return RPC_ERROR_NO_ERROR;
}
