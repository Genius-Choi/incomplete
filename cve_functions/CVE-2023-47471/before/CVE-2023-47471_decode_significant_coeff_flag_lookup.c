static inline int decode_significant_coeff_flag_lookup(thread_context* tctx,
                                                 uint8_t ctxIdxInc)
{
  logtrace(LogSlice,"# significant_coeff_flag\n");
  logtrace(LogSlice,"context: %d\n",ctxIdxInc);

  int bit = decode_CABAC_bit(&tctx->cabac_decoder,
                             &tctx->ctx_model[CONTEXT_MODEL_SIGNIFICANT_COEFF_FLAG + ctxIdxInc]);

  logtrace(LogSymbols,"$1 significant_coeff_flag=%d\n",bit);

  return bit;
}
