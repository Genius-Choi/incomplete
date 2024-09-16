static int do_send_NPSetWindowCallbackStruct(rpc_message_t *message, void *p_value)
{
  NPSetWindowCallbackStruct *ws_info = (NPSetWindowCallbackStruct *)p_value;
  int error;

  if (ws_info) {
	if ((error = rpc_message_send_uint32(message, 1)) < 0)
	  return error;
	if ((error = rpc_message_send_int32(message, ws_info->type)) < 0)
	  return error;
	if ((error = rpc_message_send_uint32(message, ws_info->visual ? XVisualIDFromVisual(ws_info->visual) : 0)) < 0)
	  return error;
	if ((error = rpc_message_send_uint32(message, ws_info->colormap)) < 0)
	  return error;
	if ((error = rpc_message_send_uint32(message, ws_info->depth)) < 0)
	  return error;
  }
  else {
	if ((error = rpc_message_send_uint32(message, 0)) < 0)
	  return error;
  }

  return RPC_ERROR_NO_ERROR;
}
