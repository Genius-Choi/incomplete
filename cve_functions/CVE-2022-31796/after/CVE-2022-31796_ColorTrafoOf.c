class ColorTrafo *HierarchicalBitmapRequester::ColorTrafoOf(bool encoding,bool disabletorgb)
{
  return m_pFrame->TablesOf()->ColorTrafoOf(m_pFrame,NULL,PixelTypeOf(),
                                            encoding,disabletorgb);
}
