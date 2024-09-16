int FLTIsFeatureIdFilterType(const char *pszValue)
{
  if (pszValue && (strcasecmp(pszValue, "FeatureId") == 0 ||
                   strcasecmp(pszValue, "GmlObjectId") == 0 ||
                   strcasecmp(pszValue, "ResourceId") == 0))

    return MS_TRUE;

  return MS_FALSE;
}
