static int decode_split_transform_flag(thread_context* tctx,
				       int log2TrafoSize)
{
  logtrace(LogSlice,"# split_transform_flag (log2TrafoSize=%d)\n",log2TrafoSize);

  int context = 5-log2TrafoSize;
  assert(context >= 0 && context <= 2);

  logtrace(LogSlice,"# context: %d\n",context);

  int bit = decode_CABAC_bit(&tctx->cabac_decoder, &tctx->ctx_model[CONTEXT_MODEL_SPLIT_TRANSFORM_FLAG + context]);
  logtrace(LogSymbols,"$1 split_transform_flag=%d\n",bit);
  return bit;
}
