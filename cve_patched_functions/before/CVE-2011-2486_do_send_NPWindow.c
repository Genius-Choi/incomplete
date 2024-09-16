static int do_send_NPWindow(rpc_message_t *message, void *p_value)
{
  NPWindow *window = (NPWindow *)p_value;
  int error;

  if (window == NULL) {
	if ((error = rpc_message_send_uint32(message, 0)) < 0)
	  return error;
  }
  else {
	if ((error = rpc_message_send_uint32(message, 1)) < 0)
	  return error;
	if ((error = do_send_NPWindowData(message, window)) < 0)
	  return error;
  }

  return RPC_ERROR_NO_ERROR;
}
