void read_coding_tree_unit(thread_context* tctx)
{
  slice_segment_header* shdr = tctx->shdr;
  de265_image* img = tctx->img;
  const seq_parameter_set& sps = img->get_sps();

  int xCtb = (tctx->CtbAddrInRS % sps.PicWidthInCtbsY);
  int yCtb = (tctx->CtbAddrInRS / sps.PicWidthInCtbsY);
  int xCtbPixels = xCtb << sps.Log2CtbSizeY;
  int yCtbPixels = yCtb << sps.Log2CtbSizeY;

  logtrace(LogSlice,"----- decode CTB %d;%d (%d;%d) POC=%d, SliceAddrRS=%d\n",
           xCtbPixels,yCtbPixels, xCtb,yCtb,
           tctx->img->PicOrderCntVal, tctx->shdr->SliceAddrRS);

  img->set_SliceAddrRS(xCtb, yCtb, tctx->shdr->SliceAddrRS);

  img->set_SliceHeaderIndex(xCtbPixels,yCtbPixels, shdr->slice_index);

  int CtbAddrInSliceSeg = tctx->CtbAddrInRS - shdr->slice_segment_address;

  if (shdr->slice_sao_luma_flag || shdr->slice_sao_chroma_flag)
    {
      read_sao(tctx, xCtb,yCtb, CtbAddrInSliceSeg);
    }

  read_coding_quadtree(tctx, xCtbPixels, yCtbPixels, sps.Log2CtbSizeY, 0);
}
