const char* FLTGetDuring(FilterEncodingNode *psFilterNode, const char** ppszTimeField)
{
  const char *pszReturn = NULL;

  if (!psFilterNode || !ppszTimeField)
    return NULL;

  if (psFilterNode->pszValue && strcasecmp(psFilterNode->pszValue, "During") == 0) {
    *ppszTimeField = psFilterNode->psLeftNode->pszValue;
    return psFilterNode->psRightNode->pszValue;
  } else {
    pszReturn = FLTGetDuring(psFilterNode->psLeftNode, ppszTimeField);
    if (pszReturn)
      return pszReturn;
    else
      return  FLTGetDuring(psFilterNode->psRightNode, ppszTimeField);
  }

  return pszReturn;
}
