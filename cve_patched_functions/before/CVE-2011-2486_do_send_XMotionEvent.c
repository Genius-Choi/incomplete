static int do_send_XMotionEvent(rpc_message_t *message, XEvent *xevent)
{
  int error;
  if ((error = do_send_XAnyEvent(message, xevent)) < 0)
	return error;
  if ((error = rpc_message_send_uint32(message, xevent->xmotion.root)) < 0)
	return error;
  if ((error = rpc_message_send_uint32(message, xevent->xmotion.subwindow)) < 0)
	return error;
  if ((error = rpc_message_send_uint32(message, xevent->xmotion.time)) < 0)
	return error;
  if ((error = rpc_message_send_int32(message, xevent->xmotion.x)) < 0)
	return error;
  if ((error = rpc_message_send_int32(message, xevent->xmotion.y)) < 0)
	return error;
  if ((error = rpc_message_send_int32(message, xevent->xmotion.x_root)) < 0)
	return error;
  if ((error = rpc_message_send_int32(message, xevent->xmotion.y_root)) < 0)
	return error;
  if ((error = rpc_message_send_uint32(message, xevent->xmotion.state)) < 0)
	return error;
  if ((error = rpc_message_send_char(message, xevent->xmotion.is_hint)) < 0)
	return error;
  if ((error = rpc_message_send_int32(message, xevent->xmotion.same_screen)) < 0)
	return error;
  return RPC_ERROR_NO_ERROR;
}
