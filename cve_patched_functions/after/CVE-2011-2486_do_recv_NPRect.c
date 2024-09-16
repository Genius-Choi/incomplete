static int do_recv_NPRect(rpc_message_t *message, void *p_value)
{
  NPRect *rect = (NPRect *)p_value;
  uint32_t top, left, bottom, right;
  int error;

  if ((error = rpc_message_recv_uint32(message, &top)) < 0)
	return error;
  if ((error = rpc_message_recv_uint32(message, &left)) < 0)
	return error;
  if ((error = rpc_message_recv_uint32(message, &bottom)) < 0)
	return error;
  if ((error = rpc_message_recv_uint32(message, &right)) < 0)
	return error;

  rect->top = top;
  rect->left = left;
  rect->bottom = bottom;
  rect->right = right;
  return RPC_ERROR_NO_ERROR;
}
