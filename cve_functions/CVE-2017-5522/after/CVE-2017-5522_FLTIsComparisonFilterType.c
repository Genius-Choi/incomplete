int FLTIsComparisonFilterType(const char *pszValue)
{
  if (pszValue) {
    if (FLTIsBinaryComparisonFilterType(pszValue) ||
        strcasecmp(pszValue, "PropertyIsLike") == 0 ||
        strcasecmp(pszValue, "PropertyIsBetween") == 0 ||
        strcasecmp(pszValue, "PropertyIsNull") == 0 ||
        strcasecmp(pszValue, "PropertyIsNil") == 0)
      return MS_TRUE;
  }

  return MS_FALSE;
}
