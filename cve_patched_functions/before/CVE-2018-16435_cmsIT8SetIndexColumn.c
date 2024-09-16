cmsBool CMSEXPORT cmsIT8SetIndexColumn(cmsHANDLE hIT8, const char* cSample)
{
    cmsIT8* it8 = (cmsIT8*) hIT8;
    int pos;

    _cmsAssert(hIT8 != NULL);

    pos = LocateSample(it8, cSample);
    if(pos == -1)
        return FALSE;

    it8->Tab[it8->nTable].SampleID = pos;
    return TRUE;
}
