int FLTIsSpatialFilterType(const char *pszValue)
{
  if (pszValue) {
    if ( strcasecmp(pszValue, "BBOX") == 0 ||
         strcasecmp(pszValue, "DWithin") == 0 ||
         strcasecmp(pszValue, "Intersect") == 0 ||
         strcasecmp(pszValue, "Intersects") == 0 ||
         strcasecmp(pszValue, "Equals") == 0 ||
         strcasecmp(pszValue, "Disjoint") == 0 ||
         strcasecmp(pszValue, "Touches") == 0 ||
         strcasecmp(pszValue, "Crosses") == 0 ||
         strcasecmp(pszValue, "Within") == 0 ||
         strcasecmp(pszValue, "Contains") == 0 ||
         strcasecmp(pszValue, "Overlaps") == 0 ||
         strcasecmp(pszValue, "Beyond") == 0)
      return MS_TRUE;
  }

  return MS_FALSE;
}
