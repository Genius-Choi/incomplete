static int decode_sao_merge_flag(thread_context* tctx)
{
  logtrace(LogSlice,"# sao_merge_left/up_flag\n");
  int bit = decode_CABAC_bit(&tctx->cabac_decoder,
                             &tctx->ctx_model[CONTEXT_MODEL_SAO_MERGE_FLAG]);

  logtrace(LogSymbols,"$1 sao_merge_flag=%d\n",bit);

  return bit;
}
