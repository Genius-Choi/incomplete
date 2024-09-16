static int decode_merge_flag(thread_context* tctx)
{
  logtrace(LogSlice,"# merge_flag\n");

  int bit = decode_CABAC_bit(&tctx->cabac_decoder,
                             &tctx->ctx_model[CONTEXT_MODEL_MERGE_FLAG]);

  logtrace(LogSymbols,"$1 merge_flag=%d\n",bit);

  return bit;
}
