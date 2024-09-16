const char *FLTGetBBOX(FilterEncodingNode *psFilterNode, rectObj *psRect)
{
  const char *pszReturn = NULL;

  if (!psFilterNode || !psRect)
    return NULL;

  if (psFilterNode->pszValue && strcasecmp(psFilterNode->pszValue, "BBOX") == 0) {
    if (psFilterNode->psRightNode && psFilterNode->psRightNode->pOther) {
      rectObj* pRect= (rectObj *)psFilterNode->psRightNode->pOther;
      psRect->minx = pRect->minx;
      psRect->miny = pRect->miny;
      psRect->maxx = pRect->maxx;
      psRect->maxy = pRect->maxy;

      return psFilterNode->pszSRS;

    }
  } else {
    pszReturn = FLTGetBBOX(psFilterNode->psLeftNode, psRect);
    if (pszReturn)
      return pszReturn;
    else
      return  FLTGetBBOX(psFilterNode->psRightNode, psRect);
  }

  return pszReturn;
}
