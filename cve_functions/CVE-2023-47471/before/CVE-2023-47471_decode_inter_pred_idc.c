static enum InterPredIdc  decode_inter_pred_idc(thread_context* tctx,
                                               int x0, int y0,
                                               int nPbW, int nPbH,
                                               int ctDepth)
{
  logtrace(LogSlice,"# inter_pred_idc\n");

  int value;

  context_model* model = &tctx->ctx_model[CONTEXT_MODEL_INTER_PRED_IDC];

  if (nPbW+nPbH==12) {
    value = decode_CABAC_bit(&tctx->cabac_decoder,
                             &model[4]);
  }
  else {
    int bit0 = decode_CABAC_bit(&tctx->cabac_decoder,
                                &model[ctDepth]);
    if (bit0==0) {
      value = decode_CABAC_bit(&tctx->cabac_decoder,
                               &model[4]);
    }
    else {
      value = 2;
    }
  }

  logtrace(LogSlice,"> inter_pred_idc = %d (%s)\n",value,
           value==0 ? "L0" : (value==1 ? "L1" : "BI"));

  logtrace(LogSymbols,"$1 decode_inter_pred_idx=%d\n",value+1);

  return (enum InterPredIdc) (value+1);
}
