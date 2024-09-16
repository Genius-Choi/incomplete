int FLTParseGMLBox(CPLXMLNode *psBox, rectObj *psBbox, char **ppszSRS)
{
  int bCoordinatesValid = 0;
  CPLXMLNode *psCoordinates = NULL;
  CPLXMLNode *psCoord1 = NULL, *psCoord2 = NULL;
  char **papszCoords=NULL, **papszMin=NULL, **papszMax = NULL;
  int nCoords = 0, nCoordsMin = 0, nCoordsMax = 0;
  const char *pszTmpCoord = NULL;
  const char *pszSRS = NULL;
  const char *pszTS = NULL;
  const char *pszCS = NULL;
  double minx = 0.0, miny = 0.0, maxx = 0.0, maxy = 0.0;

  if (psBox) {
    pszSRS = CPLGetXMLValue(psBox, "srsName", NULL);
    if (ppszSRS && pszSRS)
      *ppszSRS = msStrdup(pszSRS);

    psCoordinates = CPLGetXMLNode(psBox, "coordinates");
    pszTS = CPLGetXMLValue(psCoordinates, "ts", NULL);
    if( pszTS == NULL )
        pszTS = " ";
    pszCS = CPLGetXMLValue(psCoordinates, "cs", NULL);
    if( pszCS == NULL )
        pszCS = ",";
    pszTmpCoord = CPLGetXMLValue(psCoordinates, NULL, NULL);

    if (pszTmpCoord) {
      papszCoords = msStringSplit(pszTmpCoord, pszTS[0], &nCoords);
      if (papszCoords && nCoords == 2) {
        papszMin = msStringSplit(papszCoords[0], pszCS[0], &nCoordsMin);
        if (papszMin && nCoordsMin == 2) {
          papszMax = msStringSplit(papszCoords[1], pszCS[0], &nCoordsMax);
        }
        if (papszMax && nCoordsMax == 2) {
          bCoordinatesValid =1;
          minx =  atof(papszMin[0]);
          miny =  atof(papszMin[1]);
          maxx =  atof(papszMax[0]);
          maxy =  atof(papszMax[1]);
        }

        msFreeCharArray(papszMin, nCoordsMin);
        msFreeCharArray(papszMax, nCoordsMax);
      }

      msFreeCharArray(papszCoords, nCoords);
    } else {
      psCoord1 = CPLGetXMLNode(psBox, "coord");
      psCoord2 = FLTGetNextSibblingNode(psCoord1);
      if (psCoord1 && psCoord2 && strcmp(psCoord2->pszValue, "coord") == 0) {
        const char* pszX = CPLGetXMLValue(psCoord1, "X", NULL);
        const char* pszY = CPLGetXMLValue(psCoord1, "Y", NULL);
        if (pszX && pszY) {
          minx = atof(pszX);
          miny = atof(pszY);

          pszX = CPLGetXMLValue(psCoord2, "X", NULL);
          pszY = CPLGetXMLValue(psCoord2, "Y", NULL);
          if (pszX && pszY) {
            maxx = atof(pszX);
            maxy = atof(pszY);
            bCoordinatesValid = 1;
          }
        }
      }

    }
  }

  if (bCoordinatesValid) {
    psBbox->minx =  minx;
    psBbox->miny =  miny;

    psBbox->maxx =  maxx;
    psBbox->maxy =  maxy;
  }

  return bCoordinatesValid;
}
