LIBDE265_INLINE static int luma_pos_to_ctbAddrRS(const seq_parameter_set* sps, int x,int y)
{
  int ctbX = x >> sps->Log2CtbSizeY;
  int ctbY = y >> sps->Log2CtbSizeY;

  return ctbY * sps->PicWidthInCtbsY + ctbX;
}
