static int FLTNeedSRSSwapping( const char* pszSRS )
{
    int bNeedSwapping = MS_FALSE;
    projectionObj sProjTmp;
    msInitProjection(&sProjTmp);
    if (msLoadProjectionStringEPSG(&sProjTmp, pszSRS) == 0) {
        bNeedSwapping = msIsAxisInvertedProj(&sProjTmp);
    }
    msFreeProjection(&sProjTmp);
    return bNeedSwapping;
}
