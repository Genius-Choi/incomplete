static gboolean rpc_event_prepare(GSource *source, gint *timeout)
{
  *timeout = -1;
  return FALSE;
}
