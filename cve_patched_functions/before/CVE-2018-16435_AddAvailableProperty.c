KEYVALUE* AddAvailableProperty(cmsIT8* it8, const char* Key, WRITEMODE as)
{
    return AddToList(it8, &it8->ValidKeywords, Key, NULL, NULL, as);
}
