static int decode_rqt_root_cbf(thread_context* tctx)
{
  logtrace(LogSlice,"# rqt_root_cbf\n");

  int bit = decode_CABAC_bit(&tctx->cabac_decoder,
                             &tctx->ctx_model[CONTEXT_MODEL_RQT_ROOT_CBF]);

  logtrace(LogSymbols,"$1 rqt_root_cbf=%d\n",bit);
  return bit;
}
