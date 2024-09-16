static int do_recv_NPIdentifier(rpc_message_t *message, void *p_value)
{
  int error;
  uint32_t id;

  if ((error = rpc_message_recv_uint32(message, &id)) < 0)
	return error;

  NPIdentifier ident = NULL;
  if (id) {
#ifdef BUILD_WRAPPER
	ident = id_lookup(id);
#endif
#ifdef BUILD_VIEWER
	ident = (void *)(uintptr_t)id;
#endif
	assert(ident != NULL);
  }
  *((NPIdentifier *)p_value) = ident;
  return RPC_ERROR_NO_ERROR;
}
