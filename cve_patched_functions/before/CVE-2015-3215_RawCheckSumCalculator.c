static UINT32 RawCheckSumCalculator(PVOID buffer, ULONG len)
{
    UINT32 val = 0;
    PUSHORT pus = (PUSHORT)buffer;
    ULONG count = len >> 1;
    while (count--) val += *pus++;
    if (len & 1) val += (USHORT)*(PUCHAR)pus;
    return val;
}
