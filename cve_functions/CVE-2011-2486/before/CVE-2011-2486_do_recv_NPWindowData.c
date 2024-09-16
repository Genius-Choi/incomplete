static int do_recv_NPWindowData(rpc_message_t *message, void *p_value)
{
  NPWindow *window = (NPWindow *)p_value;
  NPSetWindowCallbackStruct *ws_info;
  uint32_t window_id;
  int32_t window_type;
  int error;

  if (window == NULL)
	return RPC_ERROR_MESSAGE_ARGUMENT_INVALID;

  if ((error = rpc_message_recv_uint32(message, &window_id)) < 0)
	return error;
  if ((error = rpc_message_recv_int32(message, &window->x)) < 0)
	return error;
  if ((error = rpc_message_recv_int32(message, &window->y)) < 0)
	return error;
  if ((error = rpc_message_recv_uint32(message, &window->width)) < 0)
	return error;
  if ((error = rpc_message_recv_uint32(message, &window->height)) < 0)
	return error;
  if ((error = do_recv_NPRect(message, &window->clipRect)) < 0)
	return error;
  if ((error = rpc_message_recv_int32(message, &window_type)) < 0)
	return error;
  if ((error = do_recv_NPSetWindowCallbackStruct(message, &ws_info)) < 0)
	return error;
  window->type = window_type;
  window->window = (void *)(Window)window_id;
  window->ws_info = ws_info;

  return RPC_ERROR_NO_ERROR;
}
