static int do_send_NPByteRange(rpc_message_t *message, void *p_value)
{
  NPByteRange *range = (NPByteRange *)p_value;
  while (range) {
	int error;
	if ((error = rpc_message_send_uint32(message, 1)) < 0)
	  return error;
	if ((error = rpc_message_send_int32(message, range->offset)) < 0)
	  return error;
	if ((error = rpc_message_send_uint32(message, range->length)) < 0)
	  return error;
	range = range->next;
  }
  return rpc_message_send_uint32(message, 0);
}
