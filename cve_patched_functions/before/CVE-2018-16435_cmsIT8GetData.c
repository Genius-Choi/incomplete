const char* CMSEXPORT cmsIT8GetData(cmsHANDLE hIT8, const char* cPatch, const char* cSample)
{
    cmsIT8* it8 = (cmsIT8*) hIT8;
    int iField, iSet;

    _cmsAssert(hIT8 != NULL);

    iField = LocateSample(it8, cSample);
    if (iField < 0) {
        return NULL;
    }

    iSet = LocatePatch(it8, cPatch);
    if (iSet < 0) {
            return NULL;
    }

    return GetData(it8, iSet, iField);
}
