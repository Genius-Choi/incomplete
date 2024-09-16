int FLTShapeFromGMLTree(CPLXMLNode *psTree, shapeObj *psShape , char **ppszSRS)
{
  const char *pszSRS = NULL;
  if (psTree && psShape) {
    CPLXMLNode *psNext = psTree->psNext;
    OGRGeometryH hGeometry = NULL;

    psTree->psNext = NULL;
    hGeometry = OGR_G_CreateFromGMLTree(psTree );
    psTree->psNext = psNext;

    if (hGeometry) {
      OGRwkbGeometryType nType;
      nType = OGR_G_GetGeometryType(hGeometry);
      if (nType == wkbPolygon25D || nType == wkbMultiPolygon25D)
        nType = wkbPolygon;
      else if (nType == wkbLineString25D || nType == wkbMultiLineString25D)
        nType = wkbLineString;
      else if (nType == wkbPoint25D  || nType ==  wkbMultiPoint25D)
        nType = wkbPoint;
      FLTogrConvertGeometry(hGeometry, psShape, nType);

      OGR_G_DestroyGeometry(hGeometry);

      pszSRS = CPLGetXMLValue(psTree, "srsName", NULL);
      if (ppszSRS && pszSRS)
        *ppszSRS = msStrdup(pszSRS);

      return MS_TRUE;
    }
  }

  return MS_FALSE;
}
