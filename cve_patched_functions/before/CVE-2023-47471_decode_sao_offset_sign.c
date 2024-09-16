static int decode_sao_offset_sign(thread_context* tctx)
{
  logtrace(LogSlice,"# sao_offset_sign\n");
  int value = decode_CABAC_bypass(&tctx->cabac_decoder);
  logtrace(LogSymbols,"$1 sao_offset_sign=%d\n",value);
  return value;
}
