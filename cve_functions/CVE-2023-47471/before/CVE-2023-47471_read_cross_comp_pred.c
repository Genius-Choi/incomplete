static void read_cross_comp_pred(thread_context* tctx, int cIdxMinus1)
{
  int log2_res_scale_abs_plus1 = decode_log2_res_scale_abs_plus1(tctx,cIdxMinus1);
  int ResScaleVal;

  if (log2_res_scale_abs_plus1 != 0) {
    int res_scale_sign_flag = decode_res_scale_sign_flag(tctx,cIdxMinus1);

    ResScaleVal = 1 << (log2_res_scale_abs_plus1 - 1);
    ResScaleVal *= 1 - 2 * res_scale_sign_flag;
  }
  else {
    ResScaleVal = 0;
  }

  tctx->ResScaleVal = ResScaleVal;
}
