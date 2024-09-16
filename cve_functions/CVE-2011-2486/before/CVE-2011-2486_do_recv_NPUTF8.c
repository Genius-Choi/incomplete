static int do_recv_NPUTF8(rpc_message_t *message, void *p_value)
{
  NPUTF8 **string_p = (NPUTF8 **)p_value;
  NPUTF8 *string = NULL;

  uint32_t len;
  int error = rpc_message_recv_uint32(message, &len);
  if (error < 0)
	return error;
  if ((string = NPN_MemAlloc(len)) == NULL)
	return RPC_ERROR_NO_MEMORY;
  if (len > 0) {
	if ((error = rpc_message_recv_bytes(message, (unsigned char *)string, len)) < 0)
	  return error;
  }

  if (string_p)
	*string_p = string;
  else if (string)
	NPN_MemFree(string);
  return RPC_ERROR_NO_ERROR;
}
