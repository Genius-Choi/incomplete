static int do_send_NPStream(rpc_message_t *message, void *p_value)
{
  uint32_t stream_id = 0;
  NPStream *stream = (NPStream *)p_value;
  if (stream) {
	NPW_StreamInstance *sip = NPW_STREAM_INSTANCE(stream);
	if (sip)
	  stream_id = sip->stream_id;
  }
  return rpc_message_send_uint32(message, stream_id);
}
