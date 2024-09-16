static inline int decode_rem_intra_luma_pred_mode(thread_context* tctx)
{
  logtrace(LogSlice,"# rem_intra_luma_pred_mode (5 bits)\n");
  int value = decode_CABAC_FL_bypass(&tctx->cabac_decoder, 5);
  logtrace(LogSymbols,"$1 rem_intra_luma_pred_mode=%d\n",value);
  return value;
}
