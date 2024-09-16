static int do_recv_NPPrint(rpc_message_t *message, void *p_value)
{
  NPPrint *printInfo = (NPPrint *)p_value;
  uint32_t print_mode;
  int error;

  if ((error = rpc_message_recv_uint32(message, &print_mode)) < 0)
	return error;
  switch (print_mode) {
  case NP_FULL:
	if ((error = do_recv_NPFullPrint(message, &printInfo->print.fullPrint)) < 0)
	  return error;
	break;
  case NP_EMBED:
	if ((error = do_recv_NPEmbedPrint(message, &printInfo->print.embedPrint)) < 0)
	  return error;
	break;
  default:
	return RPC_ERROR_GENERIC;
  }

  printInfo->mode = print_mode;
  return RPC_ERROR_NO_ERROR;
}
