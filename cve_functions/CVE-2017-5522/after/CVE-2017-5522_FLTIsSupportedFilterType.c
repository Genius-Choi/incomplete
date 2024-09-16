int FLTIsSupportedFilterType(CPLXMLNode *psXMLNode)
{
  if (psXMLNode) {
    if (FLTIsLogicalFilterType(psXMLNode->pszValue) ||
        FLTIsSpatialFilterType(psXMLNode->pszValue) ||
        FLTIsComparisonFilterType(psXMLNode->pszValue) ||
        FLTIsFeatureIdFilterType(psXMLNode->pszValue) ||
        FLTIsTemporalFilterType(psXMLNode->pszValue))
      return MS_TRUE;
  }

  return MS_FALSE;
}
