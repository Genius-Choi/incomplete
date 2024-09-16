int FLTIsGeosNode(char *pszValue)
{
  if (FLTGetGeosOperator(pszValue) == -1)
    return MS_FALSE;

  return MS_TRUE;
}
