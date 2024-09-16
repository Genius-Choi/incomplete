static int do_recv_NPStream(rpc_message_t *message, void *p_value)
{
  int error;
  uint32_t stream_id;

  if ((error = rpc_message_recv_uint32(message, &stream_id)) < 0)
	return error;

  NPW_StreamInstance *stream = id_lookup(stream_id);
  *((NPStream **)p_value) = stream ? stream->stream : NULL;
  return RPC_ERROR_NO_ERROR;
}
