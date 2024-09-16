static int decode_transform_skip_flag(thread_context* tctx, int cIdx)
{
  const int context = (cIdx==0) ? 0 : 1;

  logtrace(LogSlice,"# transform_skip_flag (context=%d)\n",context);

  int bit = decode_CABAC_bit(&tctx->cabac_decoder,
                             &tctx->ctx_model[CONTEXT_MODEL_TRANSFORM_SKIP_FLAG+context]);

  logtrace(LogSymbols,"$1 transform_skip_flag=%d\n",bit);

  return bit;
}
