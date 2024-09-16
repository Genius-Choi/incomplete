cmsBool CMSEXPORT cmsIT8SetDataRowCol(cmsHANDLE hIT8, int row, int col, const char* Val)
{
    cmsIT8* it8 = (cmsIT8*) hIT8;

    _cmsAssert(hIT8 != NULL);

    return SetData(it8, row, col, Val);
}
