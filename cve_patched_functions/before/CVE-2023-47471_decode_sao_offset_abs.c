static int decode_sao_offset_abs(thread_context* tctx, int bitDepth)
{
  logtrace(LogSlice,"# sao_offset_abs\n");
  int cMax = (1<<(libde265_min(bitDepth,10)-5))-1;
  int value = decode_CABAC_TU_bypass(&tctx->cabac_decoder, cMax);
  logtrace(LogSymbols,"$1 sao_offset_abs=%d\n",value);
  return value;
}
