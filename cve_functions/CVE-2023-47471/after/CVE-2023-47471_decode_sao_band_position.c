static int decode_sao_band_position(thread_context* tctx)
{
  logtrace(LogSlice,"# sao_band_position\n");
  int value = decode_CABAC_FL_bypass(&tctx->cabac_decoder,5);
  logtrace(LogSymbols,"$1 sao_band_position=%d\n",value);
  return value;
}
