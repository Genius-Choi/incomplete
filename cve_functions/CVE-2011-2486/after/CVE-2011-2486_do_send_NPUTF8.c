static int do_send_NPUTF8(rpc_message_t *message, void *p_value)
{
  NPUTF8 *string = (NPUTF8 *)p_value;
  if (string == NULL)
	return RPC_ERROR_MESSAGE_ARGUMENT_INVALID;

  int len = strlen(string) + 1;
  int error = rpc_message_send_uint32(message, len);
  if (error < 0)
	return error;
  if (len > 0)
	return rpc_message_send_bytes(message, (unsigned char *)string, len);

  return RPC_ERROR_NO_ERROR;
}
