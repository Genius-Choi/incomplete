static int do_send_NPRect(rpc_message_t *message, void *p_value)
{
  NPRect *rect = (NPRect *)p_value;
  int error;

  if ((error = rpc_message_send_uint32(message, rect->top)) < 0)
	return error;
  if ((error = rpc_message_send_uint32(message, rect->left)) < 0)
	return error;
  if ((error = rpc_message_send_uint32(message, rect->bottom)) < 0)
	return error;
  if ((error = rpc_message_send_uint32(message, rect->right)) < 0)
	return error;

  return RPC_ERROR_NO_ERROR;
}
