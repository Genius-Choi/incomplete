static int do_recv_XGraphicsExposeEvent(rpc_message_t *message, XEvent *xevent)
{
  int32_t x, y;
  uint32_t width, height;
  int error;
  if ((error = do_recv_XAnyEvent(message, xevent)) < 0)
	return error;
  if ((error = rpc_message_recv_int32(message, &x)) < 0)
	return error;
  if ((error = rpc_message_recv_int32(message, &y)) < 0)
	return error;
  if ((error = rpc_message_recv_uint32(message, &width)) < 0)
	return error;
  if ((error = rpc_message_recv_uint32(message, &height)) < 0)
	return error;
  xevent->xgraphicsexpose.x = x;
  xevent->xgraphicsexpose.y = y;
  xevent->xgraphicsexpose.width = width;
  xevent->xgraphicsexpose.height = height;
  return RPC_ERROR_NO_ERROR;
}
