static int do_send_NPPrint(rpc_message_t *message, void *p_value)
{
  NPPrint *printInfo = (NPPrint *)p_value;
  int error;

  if ((error = rpc_message_send_uint32(message, printInfo->mode)) < 0)
	return error;
  switch (printInfo->mode) {
  case NP_FULL:
	if ((error = do_send_NPFullPrint(message, &printInfo->print.fullPrint)) < 0)
	  return error;
	break;
  case NP_EMBED:
	if ((error = do_send_NPEmbedPrint(message, &printInfo->print.embedPrint)) < 0)
	  return error;
	break;
  default:
	return RPC_ERROR_GENERIC;
  }

  return RPC_ERROR_NO_ERROR;
}
