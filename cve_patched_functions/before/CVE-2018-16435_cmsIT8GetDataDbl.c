cmsFloat64Number CMSEXPORT cmsIT8GetDataDbl(cmsHANDLE  it8, const char* cPatch, const char* cSample)
{
    const char* Buffer;

    Buffer = cmsIT8GetData(it8, cPatch, cSample);

    return ParseFloatNumber(Buffer);
}
