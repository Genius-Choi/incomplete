static int do_send_XCrossingEvent(rpc_message_t *message, XEvent *xevent)
{
  int error;
  if ((error = do_send_XAnyEvent(message, xevent)) < 0)
	return error;
  if ((error = rpc_message_send_uint32(message, xevent->xcrossing.root)) < 0)
	return error;
  if ((error = rpc_message_send_uint32(message, xevent->xcrossing.subwindow)) < 0)
	return error;
  if ((error = rpc_message_send_uint32(message, xevent->xcrossing.time)) < 0)
	return error;
  if ((error = rpc_message_send_int32(message, xevent->xcrossing.x)) < 0)
	return error;
  if ((error = rpc_message_send_int32(message, xevent->xcrossing.y)) < 0)
	return error;
  if ((error = rpc_message_send_int32(message, xevent->xcrossing.x_root)) < 0)
	return error;
  if ((error = rpc_message_send_int32(message, xevent->xcrossing.y_root)) < 0)
	return error;
  if ((error = rpc_message_send_int32(message, xevent->xcrossing.mode)) < 0)
	return error;
  if ((error = rpc_message_send_int32(message, xevent->xcrossing.detail)) < 0)
	return error;
  if ((error = rpc_message_send_int32(message, xevent->xcrossing.same_screen)) < 0)
	return error;
  if ((error = rpc_message_send_int32(message, xevent->xcrossing.focus)) < 0)
	return error;
  if ((error = rpc_message_send_uint32(message, xevent->xcrossing.state)) < 0)
	return error;
  return RPC_ERROR_NO_ERROR;
}
