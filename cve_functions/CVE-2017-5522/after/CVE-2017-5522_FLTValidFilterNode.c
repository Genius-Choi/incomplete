int FLTValidFilterNode(FilterEncodingNode *psFilterNode)
{
  int  bReturn = 0;

  if (!psFilterNode)
    return 0;

  if (psFilterNode->eType == FILTER_NODE_TYPE_UNDEFINED)
    return 0;

  if (psFilterNode->psLeftNode) {
    bReturn = FLTValidFilterNode(psFilterNode->psLeftNode);
    if (bReturn == 0)
      return 0;
    else if (psFilterNode->psRightNode)
      return FLTValidFilterNode(psFilterNode->psRightNode);
  }

  return 1;
}
