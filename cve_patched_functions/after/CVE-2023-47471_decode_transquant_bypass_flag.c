static int decode_transquant_bypass_flag(thread_context* tctx)
{
  logtrace(LogSlice,"# cu_transquant_bypass_enable_flag\n");
  int value = decode_CABAC_bit(&tctx->cabac_decoder,
                               &tctx->ctx_model[CONTEXT_MODEL_CU_TRANSQUANT_BYPASS_FLAG]);
  logtrace(LogSymbols,"$1 transquant_bypass_flag=%d\n",value);
  return value;
}
