FilterEncodingNode *FLTCreateFeatureIdFilterEncoding(const char *pszString)
{
  FilterEncodingNode *psFilterNode = NULL;

  if (pszString) {
    psFilterNode = FLTCreateFilterEncodingNode();
    psFilterNode->eType = FILTER_NODE_TYPE_FEATUREID;
    psFilterNode->pszValue =  msStrdup(pszString);
    return psFilterNode;
  }
  return NULL;
}
