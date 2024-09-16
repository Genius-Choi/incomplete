static int decode_mvp_lx_flag(thread_context* tctx)
{
  logtrace(LogSlice,"# mvp_lx_flag\n");

  int bit = decode_CABAC_bit(&tctx->cabac_decoder,
                             &tctx->ctx_model[CONTEXT_MODEL_MVP_LX_FLAG]);

  logtrace(LogSymbols,"$1 mvp_lx_flag=%d\n",bit);
  return bit;
}
