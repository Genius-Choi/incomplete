static FilterEncodingNode* FLTGetTopBBOX(FilterEncodingNode *psNode)
{
  int nCount = 0;
  FilterEncodingNode* psTopBBOX = NULL;
  FLTGetTopBBOXInternal(psNode, &psTopBBOX, &nCount);
  return psTopBBOX;
}
