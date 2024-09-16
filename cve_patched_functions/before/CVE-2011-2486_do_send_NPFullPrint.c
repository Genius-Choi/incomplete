static int do_send_NPFullPrint(rpc_message_t *message, void *p_value)
{
  NPFullPrint *fullPrint = (NPFullPrint *)p_value;
  int error;

  if ((error = rpc_message_send_uint32(message, fullPrint->pluginPrinted)) < 0)
	return error;
  if ((error = rpc_message_send_uint32(message, fullPrint->printOne)) < 0)
	return error;

  return RPC_ERROR_NO_ERROR;
}
