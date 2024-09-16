cmsBool CMSEXPORT cmsIT8SetDataDbl(cmsHANDLE hIT8, const char* cPatch,
                                   const char* cSample,
                                   cmsFloat64Number Val)
{
    cmsIT8* it8 = (cmsIT8*) hIT8;
    char Buff[256];

    _cmsAssert(hIT8 != NULL);

    snprintf(Buff, 255, it8->DoubleFormatter, Val);
    return cmsIT8SetData(hIT8, cPatch, cSample, Buff);
}
