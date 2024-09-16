static int do_send_XGraphicsExposeEvent(rpc_message_t *message, XEvent *xevent)
{
  int error;
  if ((error = do_send_XAnyEvent(message, xevent)) < 0)
	return error;
  if ((error = rpc_message_send_int32(message, xevent->xgraphicsexpose.x)) < 0)
	return error;
  if ((error = rpc_message_send_int32(message, xevent->xgraphicsexpose.y)) < 0)
	return error;
  if ((error = rpc_message_send_uint32(message, xevent->xgraphicsexpose.width)) < 0)
	return error;
  if ((error = rpc_message_send_uint32(message, xevent->xgraphicsexpose.height)) < 0)
	return error;
  return RPC_ERROR_NO_ERROR;
}
