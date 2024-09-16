int FLTNumberOfFilterType(FilterEncodingNode *psFilterNode, const char *szType)
{
  int nCount = 0;
  int nLeftNode=0 , nRightNode = 0;

  if (!psFilterNode || !szType || !psFilterNode->pszValue)
    return 0;

  if (strcasecmp(psFilterNode->pszValue, (char*)szType) == 0)
    nCount++;

  if (psFilterNode->psLeftNode)
    nLeftNode = FLTNumberOfFilterType(psFilterNode->psLeftNode, szType);

  nCount += nLeftNode;

  if (psFilterNode->psRightNode)
    nRightNode = FLTNumberOfFilterType(psFilterNode->psRightNode, szType);
  nCount += nRightNode;

  return nCount;
}
