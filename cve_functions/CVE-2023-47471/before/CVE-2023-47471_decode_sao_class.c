static int decode_sao_class(thread_context* tctx)
{
  logtrace(LogSlice,"# sao_class\n");
  int value = decode_CABAC_FL_bypass(&tctx->cabac_decoder, 2);
  logtrace(LogSymbols,"$1 sao_class=%d\n",value);
  return value;
}
