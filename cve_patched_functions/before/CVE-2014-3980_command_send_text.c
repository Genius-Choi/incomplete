command_send_text (Fep *fep,
		   FepControlMessage *request)
{
  _fep_output_send_text (fep, request->args[0].str);
}
