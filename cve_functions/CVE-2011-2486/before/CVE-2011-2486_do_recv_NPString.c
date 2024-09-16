static int do_recv_NPString(rpc_message_t *message, void *p_value)
{
  NPString *string = (NPString *)p_value;
  if (string == NULL)
	return RPC_ERROR_MESSAGE_ARGUMENT_INVALID;
  string->UTF8Length = 0;
  string->UTF8Characters = NULL;

  int error = rpc_message_recv_uint32(message, &string->UTF8Length);
  if (error < 0)
	return error;

  if ((string->UTF8Characters = NPN_MemAlloc(string->UTF8Length + 1)) == NULL)
	return RPC_ERROR_NO_MEMORY;
  if (string->UTF8Length > 0) {
	if ((error = rpc_message_recv_bytes(message, (unsigned char *)string->UTF8Characters, string->UTF8Length)) < 0)
	  return error;
  }
  ((char *)string->UTF8Characters)[string->UTF8Length] = '\0';
  
  return RPC_ERROR_NO_ERROR;
}
