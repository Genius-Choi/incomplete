static int do_send_NPString(rpc_message_t *message, void *p_value)
{
  NPString *string = (NPString *)p_value;
  if (string == NULL)
	return RPC_ERROR_MESSAGE_ARGUMENT_INVALID;

  int error = rpc_message_send_uint32(message, string->UTF8Length);
  if (error < 0)
	return error;
  if (string->UTF8Length && string->UTF8Characters)
	return rpc_message_send_bytes(message, (unsigned char *)string->UTF8Characters, string->UTF8Length);
  return RPC_ERROR_NO_ERROR;
}
