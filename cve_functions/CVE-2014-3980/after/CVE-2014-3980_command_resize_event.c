command_resize_event (FepClient         *client,
                      FepControlMessage *request,
                      FepControlMessage *response)
{
  FepEventResize event;
  int retval;
  uint32_t intval;

  retval = _fep_control_message_read_uint32_arg (request, 0, &intval);
  if (retval < 0)
    {
      fep_log (FEP_LOG_LEVEL_WARNING, "can't read keyval");
      goto out;
    }
  event.cols = intval;

  retval = _fep_control_message_read_uint32_arg (request, 1, &intval);
  if (retval < 0)
    {
      fep_log (FEP_LOG_LEVEL_WARNING, "can't read modifiers");
      goto out;
    }
  event.rows = intval;

 out:
  response->command = FEP_CONTROL_RESPONSE;
  _fep_control_message_alloc_args (response, 2);
  _fep_control_message_write_uint8_arg (response, 0, FEP_CONTROL_RESIZE_EVENT);

  intval = retval;
  if (retval == 0 && client->filter)
    {
      event.event.type = FEP_RESIZED;
      intval = client->filter ((FepEvent *) &event, client->filter_data);
      _fep_control_message_write_uint32_arg (response, 1, intval);
    }
}
