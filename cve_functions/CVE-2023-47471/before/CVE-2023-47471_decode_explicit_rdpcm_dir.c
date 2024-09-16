static int  decode_explicit_rdpcm_dir(thread_context* tctx,int cIdx)
{
  context_model* model = &tctx->ctx_model[CONTEXT_MODEL_RDPCM_DIR];
  int value = decode_CABAC_bit(&tctx->cabac_decoder, &model[cIdx ? 1 : 0]);
  return value;
}
