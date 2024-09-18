static int do_recv_NPSavedData(rpc_message_t *message, void *p_value)
{
  NPSavedData *save_area;
  int error;
  int32_t len;
  unsigned char *buf;

  if ((error = rpc_message_recv_int32(message, &len)) < 0)
	return error;
  if (len == 0)
	save_area = NULL;
  else {
	if ((save_area = NPN_MemAlloc(sizeof(*save_area))) == NULL)
	  return RPC_ERROR_NO_MEMORY;
	if ((buf = NPN_MemAlloc(len)) == NULL)
	  return RPC_ERROR_NO_MEMORY;
	if ((error = rpc_message_recv_bytes(message, buf, len)) < 0)
	  return error;
	save_area->len = len;
	save_area->buf = buf;
  }

  if (p_value)
	*((NPSavedData **)p_value) = save_area;
  else if (save_area) {
	NPN_MemFree(save_area->buf);
	NPN_MemFree(save_area);
  }

  return RPC_ERROR_NO_ERROR;
}
