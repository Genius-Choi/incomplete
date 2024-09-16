static gboolean rpc_event_check(GSource *source)
{
  return rpc_wait_dispatch(g_rpc_connection, 0) > 0;
}
