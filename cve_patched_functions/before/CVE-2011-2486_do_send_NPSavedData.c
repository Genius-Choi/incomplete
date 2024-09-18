static int do_send_NPSavedData(rpc_message_t *message, void *p_value)
{
  NPSavedData *save_area = (NPSavedData *)p_value;
  int error;

  if (save_area == NULL) {
	if ((error = rpc_message_send_int32(message, 0)) < 0)
	  return error;
  }
  else {
	if ((error = rpc_message_send_int32(message, save_area->len)) < 0)
	  return error;
	if ((error = rpc_message_send_bytes(message, save_area->buf, save_area->len)) < 0)
	  return error;
  }

  return RPC_ERROR_NO_ERROR;
}
