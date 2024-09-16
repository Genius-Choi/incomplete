static int decode_intra_chroma_pred_mode(thread_context* tctx)
{
  logtrace(LogSlice,"# intra_chroma_pred_mode\n");

  int prefix = decode_CABAC_bit(&tctx->cabac_decoder, &tctx->ctx_model[CONTEXT_MODEL_INTRA_CHROMA_PRED_MODE]);

  int mode;
  if (prefix==0) {
    mode=4;
  }
  else {
    mode = decode_CABAC_FL_bypass(&tctx->cabac_decoder, 2);
  }

  logtrace(LogSlice,"> intra_chroma_pred_mode = %d\n",mode);
  logtrace(LogSymbols,"$1 intra_chroma_pred_mode=%d\n",mode);

  return mode;
}
