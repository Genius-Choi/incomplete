void read_prediction_unit_SKIP(thread_context* tctx,
                               int x0, int y0,
                               int nPbW, int nPbH)
{
  int merge_idx = decode_merge_idx(tctx);

  tctx->motion.merge_idx = merge_idx;
  tctx->motion.merge_flag = true;

  logtrace(LogSlice,"prediction skip 2Nx2N, merge_idx: %d\n",merge_idx);
}
