char *FLTGetCommonExpression(FilterEncodingNode *psFilterNode, layerObj *lp)
{
  char *pszExpression = NULL;

  if (!psFilterNode)
    return NULL;

  if (psFilterNode->eType == FILTER_NODE_TYPE_COMPARISON) {
    if ( psFilterNode->psLeftNode && psFilterNode->psRightNode) {
      if (FLTIsBinaryComparisonFilterType(psFilterNode->pszValue))
        pszExpression = FLTGetBinaryComparisonCommonExpression(psFilterNode, lp);
      else if (strcasecmp(psFilterNode->pszValue, "PropertyIsLike") == 0)
        pszExpression = FLTGetIsLikeComparisonCommonExpression(psFilterNode);
      else if (strcasecmp(psFilterNode->pszValue, "PropertyIsBetween") == 0)
        pszExpression = FLTGetIsBetweenComparisonCommonExpresssion(psFilterNode, lp);
    }
  } else if (psFilterNode->eType == FILTER_NODE_TYPE_LOGICAL) {
    pszExpression = FLTGetLogicalComparisonCommonExpression(psFilterNode, lp);
  } else if (psFilterNode->eType == FILTER_NODE_TYPE_SPATIAL) {
    pszExpression = FLTGetSpatialComparisonCommonExpression(psFilterNode, lp);
  } else if (psFilterNode->eType ==  FILTER_NODE_TYPE_FEATUREID) {
    pszExpression = FLTGetFeatureIdCommonExpression(psFilterNode, lp);
  } else if (psFilterNode->eType == FILTER_NODE_TYPE_TEMPORAL) {
    pszExpression = FLTGetTimeExpression(psFilterNode, lp);
  }

  return pszExpression;
}
