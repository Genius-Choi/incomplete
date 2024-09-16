void initialize_CABAC_models(thread_context* tctx)
{
  const int QPY = tctx->shdr->SliceQPY;
  const int initType = tctx->shdr->initType;
  assert(initType >= 0 && initType <= 2);

  tctx->ctx_model.init(initType, QPY);

  for (int i=0;i<4;i++) {
    tctx->StatCoeff[i] = 0;
  }
}
