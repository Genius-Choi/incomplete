static int do_send_NotifyData(rpc_message_t *message, void *p_value)
{
  void *notifyData = (void *)p_value;
  return rpc_message_send_uint64(message, (uintptr_t)notifyData);
}
