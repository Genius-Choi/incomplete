const char* CMSEXPORT cmsIT8GetProperty(cmsHANDLE hIT8, const char* Key)
{
    cmsIT8* it8 = (cmsIT8*) hIT8;
    KEYVALUE* p;

    if (IsAvailableOnList(GetTable(it8) -> HeaderList, Key, NULL, &p))
    {
        return p -> Value;
    }
    return NULL;
}
