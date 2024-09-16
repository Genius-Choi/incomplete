void HierarchicalBitmapRequester::BuildCommon(void)
{
  BitmapCtrl::BuildCommon();
  if (m_ppTempIBM == NULL) {
    m_ppTempIBM = (struct ImageBitMap **)m_pEnviron->AllocMem(sizeof(struct ImageBitMap **) * m_ucCount);
    memset(m_ppTempIBM,0,sizeof(struct ImageBitMap *) * m_ucCount);
    for (UBYTE i = 0;i < m_ucCount;i++) {
      m_ppTempIBM[i] = new(m_pEnviron) struct ImageBitMap();
    }
  }

  if (m_pulReadyLines == NULL) {
    m_pulReadyLines = (ULONG *)m_pEnviron->AllocMem(sizeof(ULONG) * m_ucCount);
    memset(m_pulReadyLines,0,sizeof(ULONG) * m_ucCount);
  }

  if (m_pulY == NULL) {
    m_pulY = (ULONG *)m_pEnviron->AllocMem(sizeof(ULONG) * m_ucCount);
    memset(m_pulY,0,sizeof(ULONG) * m_ucCount);
  }

  if (m_pulHeight == NULL) {
    m_pulHeight = (ULONG *)m_pEnviron->AllocMem(sizeof(ULONG) * m_ucCount);
    for(UBYTE i = 0;i < m_ucCount;i++) {
      class Component *comp = m_pFrame->ComponentOf(i);
      UBYTE suby            = comp->SubYOf();
      m_pulHeight[i]        = (m_ulPixelHeight + suby - 1) / suby;
    }
  }
}
