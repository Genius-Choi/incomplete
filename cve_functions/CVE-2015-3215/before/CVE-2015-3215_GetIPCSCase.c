static LPCSTR __inline GetIPCSCase(tTcpIpPacketParsingResult res)
{
    static const char *const CSCaseName[4] = { "not tested", "(too short)", "OK", "Bad" };
    return CSCaseName[res.ipCheckSum];
}
