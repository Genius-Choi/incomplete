command_forward_key_event (Fep *fep,
			   FepControlMessage *request)
{
  uint32_t keyval, modifiers;
  if (_fep_control_message_read_uint32_arg (request, 0, &keyval) == 0
      && _fep_control_message_read_uint32_arg (request, 1, &modifiers) == 0)
    {
      size_t length;
      char *data = _fep_key_to_string (keyval, modifiers, &length);
      if (data)
	{
	  _fep_output_send_data (fep, data, length);
	  free (data);
	}
    }
}
