int FLTIsLineFilter(FilterEncodingNode *psFilterNode)
{
  if (!psFilterNode || !psFilterNode->pszValue)
    return 0;

  if (psFilterNode->eType == FILTER_NODE_TYPE_SPATIAL &&
      psFilterNode->psRightNode &&
      psFilterNode->psRightNode->eType == FILTER_NODE_TYPE_GEOMETRY_LINE)
    return 1;

  return 0;
}
