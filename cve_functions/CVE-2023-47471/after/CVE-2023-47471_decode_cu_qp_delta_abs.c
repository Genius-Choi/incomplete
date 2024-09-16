static int decode_cu_qp_delta_abs(thread_context* tctx)
{
  logtrace(LogSlice,"# cu_qp_delta_abs\n");

  int bit = decode_CABAC_bit(&tctx->cabac_decoder,
                             &tctx->ctx_model[CONTEXT_MODEL_CU_QP_DELTA_ABS + 0]);
  if (bit==0) {
    logtrace(LogSymbols,"$1 cu_qp_delta_abs=%d\n",0);
    return 0;
  }

  int prefix=1;
  for (int i=0;i<4;i++) {
    bit = decode_CABAC_bit(&tctx->cabac_decoder,
                           &tctx->ctx_model[CONTEXT_MODEL_CU_QP_DELTA_ABS + 1]);
    if (bit==0) { break; }
    else { prefix++; }
  }

  if (prefix==5) {
    int value = decode_CABAC_EGk_bypass(&tctx->cabac_decoder, 0);
    logtrace(LogSymbols,"$1 cu_qp_delta_abs=%d\n",value+5);
    return value + 5;
  }
  else {
    logtrace(LogSymbols,"$1 cu_qp_delta_abs=%d\n",prefix);
    return prefix;
  }
}
