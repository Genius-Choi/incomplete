int FLTIsBinaryComparisonFilterType(const char *pszValue)
{
  if (pszValue) {
    if (strcasecmp(pszValue, "PropertyIsEqualTo") == 0 ||
        strcasecmp(pszValue, "PropertyIsNotEqualTo") == 0 ||
        strcasecmp(pszValue, "PropertyIsLessThan") == 0 ||
        strcasecmp(pszValue, "PropertyIsGreaterThan") == 0 ||
        strcasecmp(pszValue, "PropertyIsLessThanOrEqualTo") == 0 ||
        strcasecmp(pszValue, "PropertyIsGreaterThanOrEqualTo") == 0)
      return MS_TRUE;
  }

  return MS_FALSE;
}
