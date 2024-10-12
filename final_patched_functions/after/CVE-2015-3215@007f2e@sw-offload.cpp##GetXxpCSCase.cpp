static LPCSTR __inline GetXxpCSCase(tTcpIpPacketParsingResult res)
{
    static const char *const CSCaseName[4] = { "-", "PCS", "CS", "Bad" };
    return CSCaseName[res.xxpCheckSum];
}
