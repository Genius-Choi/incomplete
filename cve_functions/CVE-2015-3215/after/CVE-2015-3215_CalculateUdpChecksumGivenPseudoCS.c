static __inline VOID CalculateUdpChecksumGivenPseudoCS(UDPHeader *pUdpHeader, tCompletePhysicalAddress *pDataPages, ULONG ulStartOffset, ULONG udpLength)
{
    pUdpHeader->udp_xsum = CheckSumCalculator(pDataPages, ulStartOffset, udpLength);
}
