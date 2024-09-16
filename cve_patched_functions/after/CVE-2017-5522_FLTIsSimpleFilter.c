int FLTIsSimpleFilter(FilterEncodingNode *psNode)
{
  if (FLTValidForBBoxFilter(psNode)) {
    if (FLTNumberOfFilterType(psNode, "DWithin") == 0 &&
        FLTNumberOfFilterType(psNode, "Intersect") == 0 &&
        FLTNumberOfFilterType(psNode, "Intersects") == 0 &&
        FLTNumberOfFilterType(psNode, "Equals") == 0 &&
        FLTNumberOfFilterType(psNode, "Disjoint") == 0 &&
        FLTNumberOfFilterType(psNode, "Touches") == 0 &&
        FLTNumberOfFilterType(psNode, "Crosses") == 0 &&
        FLTNumberOfFilterType(psNode, "Within") == 0 &&
        FLTNumberOfFilterType(psNode, "Contains") == 0 &&
        FLTNumberOfFilterType(psNode, "Overlaps") == 0 &&
        FLTNumberOfFilterType(psNode, "Beyond") == 0)
      return TRUE;
  }

  return FALSE;
}
