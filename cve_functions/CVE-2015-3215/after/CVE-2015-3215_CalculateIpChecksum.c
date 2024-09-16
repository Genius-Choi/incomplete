static __inline VOID CalculateIpChecksum(IPv4Header *pIpHeader)
{
    pIpHeader->ip_xsum = 0;
    pIpHeader->ip_xsum = CheckSumCalculatorFlat(pIpHeader, IP_HEADER_LENGTH(pIpHeader));
}
