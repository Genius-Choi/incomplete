static int decode_cbf_luma(thread_context* tctx,
			   int trafoDepth)
{
  logtrace(LogSlice,"# cbf_luma\n");

  int bit = decode_CABAC_bit(&tctx->cabac_decoder, &tctx->ctx_model[CONTEXT_MODEL_CBF_LUMA + (trafoDepth==0)]);

  logtrace(LogSlice,"> cbf_luma = %d\n",bit);

  logtrace(LogSymbols,"$1 cbf_luma=%d\n",bit);
  return bit;
}
