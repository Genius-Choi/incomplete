static int do_send_XButtonEvent(rpc_message_t *message, XEvent *xevent)
{
  int error;
  if ((error = do_send_XAnyEvent(message, xevent)) < 0)
	return error;
  if ((error = rpc_message_send_uint32(message, xevent->xbutton.root)) < 0)
	return error;
  if ((error = rpc_message_send_uint32(message, xevent->xbutton.subwindow)) < 0)
	return error;
  if ((error = rpc_message_send_uint32(message, xevent->xbutton.time)) < 0)
	return error;
  if ((error = rpc_message_send_int32(message, xevent->xbutton.x)) < 0)
	return error;
  if ((error = rpc_message_send_int32(message, xevent->xbutton.y)) < 0)
	return error;
  if ((error = rpc_message_send_int32(message, xevent->xbutton.x_root)) < 0)
	return error;
  if ((error = rpc_message_send_int32(message, xevent->xbutton.y_root)) < 0)
	return error;
  if ((error = rpc_message_send_uint32(message, xevent->xbutton.state)) < 0)
	return error;
  if ((error = rpc_message_send_uint32(message, xevent->xbutton.button)) < 0)
	return error;
  if ((error = rpc_message_send_int32(message, xevent->xbutton.same_screen)) < 0)
	return error;
  return RPC_ERROR_NO_ERROR;
}
