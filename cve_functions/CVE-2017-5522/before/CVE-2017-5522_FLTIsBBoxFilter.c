int FLTIsBBoxFilter(FilterEncodingNode *psFilterNode)
{
  if (!psFilterNode || !psFilterNode->pszValue)
    return 0;

  if (strcasecmp(psFilterNode->pszValue, "BBOX") == 0)
    return 1;

  return 0;
}
