static int do_send_XAnyEvent(rpc_message_t *message, XEvent *xevent)
{
  int error;
  if ((error = rpc_message_send_uint32(message, xevent->xany.serial)) < 0)
	return error;
  if ((error = rpc_message_send_uint32(message, xevent->xany.send_event)) < 0)
	return error;
  if ((error = rpc_message_send_uint32(message, xevent->xany.window)) < 0)
	return error;
  return RPC_ERROR_NO_ERROR;
}
