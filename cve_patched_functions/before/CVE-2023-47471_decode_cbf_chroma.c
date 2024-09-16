static int decode_cbf_chroma(thread_context* tctx,
			     int trafoDepth)
{
  logtrace(LogSlice,"# cbf_chroma\n");

  int bit = decode_CABAC_bit(&tctx->cabac_decoder, &tctx->ctx_model[CONTEXT_MODEL_CBF_CHROMA + trafoDepth]);

  logtrace(LogSymbols,"$1 cbf_chroma=%d\n",bit);
  return bit;
}
