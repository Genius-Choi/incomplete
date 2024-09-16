fep_client_set_cursor_text (FepClient    *client,
                            const char   *text,
                            FepAttribute *attr)
{
  FepControlMessage message;

  message.command = FEP_CONTROL_SET_CURSOR_TEXT;
  _fep_control_message_alloc_args (&message, 2);
  _fep_control_message_write_string_arg (&message, 0, text, strlen (text) + 1);
  _fep_control_message_write_attribute_arg (&message, 1, attr ? attr : &empty_attr);

  if (client->filter_running)
    client->messages = _fep_append_control_message (client->messages, &message);
  else
    _fep_write_control_message (client->control, &message);
  _fep_control_message_free_args (&message);
}
