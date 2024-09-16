static __inline USHORT RawCheckSumFinalize(UINT32 val)
{
    val = (((val >> 16) | (val << 16)) + val) >> 16;
    return (USHORT)~val;
}
