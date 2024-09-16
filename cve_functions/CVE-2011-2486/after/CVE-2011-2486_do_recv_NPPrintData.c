static int do_recv_NPPrintData(rpc_message_t *message, void *p_value)
{
  NPPrintData *printData = (NPPrintData *)p_value;
  int error;

  if ((error = rpc_message_recv_uint32(message, &printData->size)) < 0)
	return error;
  if ((error = rpc_message_recv_bytes(message, printData->data, printData->size)) < 0)
	return error;

  return RPC_ERROR_NO_ERROR;
}
