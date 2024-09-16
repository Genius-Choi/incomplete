static __inline USHORT CheckSumCalculator(tCompletePhysicalAddress *pDataPages, ULONG ulStartOffset, ULONG len)
{
    tCompletePhysicalAddress *pCurrentPage = &pDataPages[0];
    ULONG ulCurrPageOffset = 0;
    UINT32 u32RawCSum = 0;

    while(ulStartOffset > 0)
    {
        ulCurrPageOffset = min(pCurrentPage->size, ulStartOffset);

        if(ulCurrPageOffset < ulStartOffset)
            pCurrentPage++;

        ulStartOffset -= ulCurrPageOffset;
    }

    while(len > 0)
    {
        PVOID pCurrentPageDataStart = RtlOffsetToPointer(pCurrentPage->Virtual, ulCurrPageOffset);
        ULONG ulCurrentPageDataLength = min(len, pCurrentPage->size - ulCurrPageOffset);

        u32RawCSum += RawCheckSumCalculator(pCurrentPageDataStart, ulCurrentPageDataLength);
        pCurrentPage++;
        ulCurrPageOffset = 0;
        len -= ulCurrentPageDataLength;
    }

    return RawCheckSumFinalize(u32RawCSum);
}
