_fep_dispatch_control_message (Fep *fep, FepControlMessage *message)
{
  static const struct
  {
    int command;
    void (*handler) (Fep *fep,
		     FepControlMessage *request);
  } handlers[] =
      {
	{ FEP_CONTROL_SET_CURSOR_TEXT, command_set_cursor_text },
	{ FEP_CONTROL_SET_STATUS_TEXT, command_set_status_text },
	{ FEP_CONTROL_SEND_TEXT, command_send_text },
	{ FEP_CONTROL_SEND_DATA, command_send_data },
	{ FEP_CONTROL_FORWARD_KEY_EVENT, command_forward_key_event }
      };
  int i;

  for (i = 0;
       i < SIZEOF (handlers) && handlers[i].command != message->command;
       i++)
    ;
  if (i == SIZEOF (handlers))
    {
      fep_log (FEP_LOG_LEVEL_WARNING,
	       "no handler defined for %d", message->command);
      return -1;
    }

  handlers[i].handler (fep, message);
  return 0;
}
