static int decode_pred_mode_flag(thread_context* tctx)
{
  logtrace(LogSlice,"# pred_mode_flag\n");

  int bit = decode_CABAC_bit(&tctx->cabac_decoder,
                             &tctx->ctx_model[CONTEXT_MODEL_PRED_MODE_FLAG]);

  logtrace(LogSymbols,"$1 pred_mode=%d\n",bit);
  return bit;
}
