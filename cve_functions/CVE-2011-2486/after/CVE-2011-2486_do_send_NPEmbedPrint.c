static int do_send_NPEmbedPrint(rpc_message_t *message, void *p_value)
{
  NPEmbedPrint *embedPrint = (NPEmbedPrint *)p_value;
  int error;

  if ((error = do_send_NPWindowData(message, &embedPrint->window)) < 0)
	return error;

  return RPC_ERROR_NO_ERROR;
}
