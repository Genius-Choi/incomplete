bool setCtbAddrFromTS(thread_context* tctx)
{
  const seq_parameter_set& sps = tctx->img->get_sps();

  if (tctx->CtbAddrInTS < sps.PicSizeInCtbsY) {
    tctx->CtbAddrInRS = tctx->img->get_pps().CtbAddrTStoRS[tctx->CtbAddrInTS];

    tctx->CtbX = tctx->CtbAddrInRS % sps.PicWidthInCtbsY;
    tctx->CtbY = tctx->CtbAddrInRS / sps.PicWidthInCtbsY;
    return false;
  }
  else {
    tctx->CtbAddrInRS = sps.PicSizeInCtbsY;

    tctx->CtbX = tctx->CtbAddrInRS % sps.PicWidthInCtbsY;
    tctx->CtbY = tctx->CtbAddrInRS / sps.PicWidthInCtbsY;
    return true;
  }
}
