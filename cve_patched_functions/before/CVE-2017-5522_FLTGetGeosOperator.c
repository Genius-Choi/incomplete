int FLTGetGeosOperator(char *pszValue)
{
  if (!pszValue)
    return -1;

  if (strcasecmp(pszValue, "Equals") == 0)
    return MS_GEOS_EQUALS;
  else if (strcasecmp(pszValue, "Intersect") == 0 ||
           strcasecmp(pszValue, "Intersects") == 0)
    return MS_GEOS_INTERSECTS;
  else if (strcasecmp(pszValue, "Disjoint") == 0)
    return MS_GEOS_DISJOINT;
  else if (strcasecmp(pszValue, "Touches") == 0)
    return MS_GEOS_TOUCHES;
  else if (strcasecmp(pszValue, "Crosses") == 0)
    return MS_GEOS_CROSSES;
  else if (strcasecmp(pszValue, "Within") == 0)
    return MS_GEOS_WITHIN;
  else if (strcasecmp(pszValue, "Contains") == 0)
    return MS_GEOS_CONTAINS;
  else if (strcasecmp(pszValue, "Overlaps") == 0)
    return MS_GEOS_OVERLAPS;
  else if (strcasecmp(pszValue, "Beyond") == 0)
    return MS_GEOS_BEYOND;
  else if (strcasecmp(pszValue, "DWithin") == 0)
    return MS_GEOS_DWITHIN;

  return -1;
}
