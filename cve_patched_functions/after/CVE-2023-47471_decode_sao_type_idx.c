static int decode_sao_type_idx(thread_context* tctx)
{
  logtrace(LogSlice,"# sao_type_idx_luma/chroma\n");

  int bit0 = decode_CABAC_bit(&tctx->cabac_decoder,
                              &tctx->ctx_model[CONTEXT_MODEL_SAO_TYPE_IDX]);

  if (bit0==0) {
    logtrace(LogSymbols,"$1 sao_type_idx=%d\n",0);
    return 0;
  }
  else {
    int bit1 = decode_CABAC_bypass(&tctx->cabac_decoder);
    if (bit1==0) {
      logtrace(LogSymbols,"$1 sao_type_idx=%d\n",1);
      return 1;
    }
    else {
      logtrace(LogSymbols,"$1 sao_type_idx=%d\n",2);
      return 2;
    }
  }
}
