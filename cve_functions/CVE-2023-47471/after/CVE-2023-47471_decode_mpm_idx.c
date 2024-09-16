static inline int decode_mpm_idx(thread_context* tctx)
{
  logtrace(LogSlice,"# mpm_idx (TU:2)\n");
  int mpm = decode_CABAC_TU_bypass(&tctx->cabac_decoder, 2);
  logtrace(LogSlice,"> mpm_idx = %d\n",mpm);
  logtrace(LogSymbols,"$1 mpm_idx=%d\n",mpm);
  return mpm;
}
