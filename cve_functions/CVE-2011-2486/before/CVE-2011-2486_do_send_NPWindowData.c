static int do_send_NPWindowData(rpc_message_t *message, void *p_value)
{
  NPWindow *window = (NPWindow *)p_value;
  int error;

  if (window == NULL)
	return RPC_ERROR_MESSAGE_ARGUMENT_INVALID;

  if ((error = rpc_message_send_uint32(message, (Window)window->window)) < 0)
	return error;
  if ((error = rpc_message_send_int32(message, window->x)) < 0)
	return error;
  if ((error = rpc_message_send_int32(message, window->y)) < 0)
	return error;
  if ((error = rpc_message_send_uint32(message, window->width)) < 0)
	return error;
  if ((error = rpc_message_send_uint32(message, window->height)) < 0)
	return error;
  if ((error = do_send_NPRect(message, &window->clipRect)) < 0)
	return error;
  if ((error = rpc_message_send_int32(message, window->type)) < 0)
	return error;
  if ((error = do_send_NPSetWindowCallbackStruct(message, window->ws_info)) < 0)
	return 0;

  return RPC_ERROR_NO_ERROR;
}
