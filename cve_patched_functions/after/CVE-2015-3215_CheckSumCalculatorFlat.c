static __inline USHORT CheckSumCalculatorFlat(PVOID buffer, ULONG len)
{
    return RawCheckSumFinalize(RawCheckSumCalculator(buffer, len));
}
