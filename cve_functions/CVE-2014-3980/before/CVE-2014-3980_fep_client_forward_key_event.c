fep_client_forward_key_event (FepClient      *client,
                              unsigned int    keyval,
                              FepModifierType modifiers)
{
  FepControlMessage message;

  message.command = FEP_CONTROL_FORWARD_KEY_EVENT;
  _fep_control_message_alloc_args (&message, 2);
  _fep_control_message_write_uint32_arg (&message, 0, keyval);
  _fep_control_message_write_uint32_arg (&message, 1, modifiers);

  if (client->filter_running)
    client->messages = _fep_append_control_message (client->messages, &message);
  else
    _fep_write_control_message (client->control, &message);
  _fep_control_message_free_args (&message);
}
