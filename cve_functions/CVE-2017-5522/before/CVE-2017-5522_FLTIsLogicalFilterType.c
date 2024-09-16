int FLTIsLogicalFilterType(const char *pszValue)
{
  if (pszValue) {
    if (strcasecmp(pszValue, "AND") == 0 ||
        strcasecmp(pszValue, "OR") == 0 ||
        strcasecmp(pszValue, "NOT") == 0)
      return MS_TRUE;
  }

  return MS_FALSE;
}
