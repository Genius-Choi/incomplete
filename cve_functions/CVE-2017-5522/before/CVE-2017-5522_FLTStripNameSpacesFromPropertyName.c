static void FLTStripNameSpacesFromPropertyName(FilterEncodingNode *psFilterNode)
{
  char **tokens=NULL;
  int n=0;

  if (psFilterNode) {

    if (psFilterNode->eType == FILTER_NODE_TYPE_COMPARISON &&
        psFilterNode->psLeftNode != NULL &&
        psFilterNode->psLeftNode->eType == FILTER_NODE_TYPE_PROPERTYNAME &&
        FLTIsGMLDefaultProperty(psFilterNode->psLeftNode->pszValue) )
    {
        return;
    }

    if (psFilterNode->eType == FILTER_NODE_TYPE_PROPERTYNAME) {
      if (psFilterNode->pszValue &&
          strstr(psFilterNode->pszValue, ":")) {
        tokens = msStringSplit(psFilterNode->pszValue, ':', &n);
        if (tokens && n==2) {
          msFree(psFilterNode->pszValue);
          psFilterNode->pszValue = msStrdup(tokens[1]);
        }
        msFreeCharArray(tokens, n);
      }
    }
    if (psFilterNode->psLeftNode)
      FLTStripNameSpacesFromPropertyName(psFilterNode->psLeftNode);
    if (psFilterNode->psRightNode)
      FLTStripNameSpacesFromPropertyName(psFilterNode->psRightNode);
  }

}
