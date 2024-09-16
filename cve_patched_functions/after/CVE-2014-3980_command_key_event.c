command_key_event (FepClient *client,
		   FepControlMessage *request,
		   FepControlMessage *response)
{
  FepEventKey event;
  int retval;
  uint32_t intval;

  retval = _fep_control_message_read_uint32_arg (request, 0, &intval);
  if (retval < 0)
    {
      fep_log (FEP_LOG_LEVEL_WARNING, "can't read keyval");
      goto out;
    }
  event.keyval = intval;

  retval = _fep_control_message_read_uint32_arg (request, 1, &intval);
  if (retval < 0)
    {
      fep_log (FEP_LOG_LEVEL_WARNING, "can't read modifiers");
      goto out;
    }
  event.modifiers = intval;

 out:
  response->command = FEP_CONTROL_RESPONSE;
  _fep_control_message_alloc_args (response, 2);
  _fep_control_message_write_uint8_arg (response, 0, FEP_CONTROL_KEY_EVENT);

  intval = retval;
  if (retval == 0 && client->filter)
    {
      event.event.type = FEP_KEY_PRESS;
      event.source = request->args[2].str;
      event.source_length = request->args[2].len;
      intval = client->filter ((FepEvent *) &event, client->filter_data);
      _fep_control_message_write_uint32_arg (response, 1, intval);
    }

  /* If key is not handled, send back the original input to the server. */
  if (intval == 0)
    fep_client_send_data (client, request->args[2].str, request->args[2].len);
}
