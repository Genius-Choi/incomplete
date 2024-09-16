static int do_recv_NPWindow(rpc_message_t *message, void *p_value)
{
  NPWindow **window_p = (NPWindow **)p_value;
  NPWindow *window;
  uint32_t window_valid;
  int error;

  if (window_p)
	*window_p = NULL;
  if ((error = rpc_message_recv_uint32(message, &window_valid)) < 0)
	return error;
  if (window_valid) {
	if ((window = malloc(sizeof(NPWindow))) == NULL)
	  return RPC_ERROR_NO_MEMORY;
	if ((error = do_recv_NPWindowData(message, window)) < 0) {
	  free(window);
	  return error;
	}
	if (window_p)
	  *window_p = window;
  }

  return RPC_ERROR_NO_ERROR;
}
