static gboolean delayed_calls_process_cb(gpointer user_data)
{
  return delayed_calls_process(NULL, FALSE);
}
