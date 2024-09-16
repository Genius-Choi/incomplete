static int FLTGetTopBBOXInternal(FilterEncodingNode *psNode, FilterEncodingNode** ppsTopBBOX, int *pnCount)
{
  if (psNode->pszValue && strcasecmp(psNode->pszValue, "BBOX") == 0) {
    (*pnCount) ++;
    if( *pnCount == 1 )
    {
      *ppsTopBBOX = psNode;
      return TRUE;
    }
    *ppsTopBBOX = NULL;
    return FALSE;
  }
  else if (psNode->pszValue && strcasecmp(psNode->pszValue, "AND") == 0) {
    return FLTGetTopBBOXInternal(psNode->psLeftNode, ppsTopBBOX, pnCount) &&
           FLTGetTopBBOXInternal(psNode->psRightNode, ppsTopBBOX, pnCount);
  }
  else
  {
    return TRUE;
  }
}
