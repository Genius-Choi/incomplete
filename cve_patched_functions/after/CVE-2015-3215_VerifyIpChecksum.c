VerifyIpChecksum(
    IPv4Header *pIpHeader,
    tTcpIpPacketParsingResult known,
    BOOLEAN bFix)
{
    tTcpIpPacketParsingResult res = known;
    if (res.ipCheckSum != ppresIPTooShort)
    {
        USHORT saved = pIpHeader->ip_xsum;
        CalculateIpChecksum(pIpHeader);
        res.ipCheckSum = CompareNetCheckSumOnEndSystem(pIpHeader->ip_xsum, saved) ? ppresCSOK : ppresCSBad;
        if (!bFix)
            pIpHeader->ip_xsum = saved;
        else
            res.fixedIpCS = res.ipCheckSum == ppresCSBad;
    }
    return res;
}
