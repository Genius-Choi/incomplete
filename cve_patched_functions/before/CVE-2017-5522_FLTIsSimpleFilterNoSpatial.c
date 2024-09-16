int FLTIsSimpleFilterNoSpatial(FilterEncodingNode *psNode)
{
  if (FLTIsSimpleFilter(psNode) && FLTNumberOfFilterType(psNode, "BBOX") == 0)
    return MS_TRUE;

  return MS_FALSE;
}
