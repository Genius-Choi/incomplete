char *FLTGetNodeExpression(FilterEncodingNode *psFilterNode, layerObj *lp)
{
  char *pszExpression = NULL;
  if (!psFilterNode)
    return NULL;

  if (FLTIsLogicalFilterType(psFilterNode->pszValue))
    pszExpression = FLTGetLogicalComparisonExpresssion(psFilterNode, lp);
  else if (FLTIsComparisonFilterType(psFilterNode->pszValue)) {
    if (FLTIsBinaryComparisonFilterType(psFilterNode->pszValue))
      pszExpression = FLTGetBinaryComparisonExpresssion(psFilterNode, lp);
    else if (strcasecmp(psFilterNode->pszValue, "PropertyIsBetween") == 0)
      pszExpression = FLTGetIsBetweenComparisonExpresssion(psFilterNode, lp);
    else if (strcasecmp(psFilterNode->pszValue, "PropertyIsLike") == 0)
      pszExpression = FLTGetIsLikeComparisonExpression(psFilterNode);
  }

  return pszExpression;
}
