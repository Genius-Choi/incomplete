static inline int decode_prev_intra_luma_pred_flag(thread_context* tctx)
{
  logtrace(LogSlice,"# prev_intra_luma_pred_flag\n");
  int bit = decode_CABAC_bit(&tctx->cabac_decoder, &tctx->ctx_model[CONTEXT_MODEL_PREV_INTRA_LUMA_PRED_FLAG]);
  logtrace(LogSymbols,"$1 prev_intra_luma_pred_flag=%d\n",bit);
  return bit;
}
