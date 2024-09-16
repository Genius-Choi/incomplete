static __inline VOID PrintOutParsingResult(
    tTcpIpPacketParsingResult res,
    int level,
    LPCSTR procname)
{
    DPrintf(level, ("[%s] %s packet IPCS %s%s, checksum %s%s\n", procname,
        GetPacketCase(res),
        GetIPCSCase(res),
        res.fixedIpCS ? "(fixed)" : "",
        GetXxpCSCase(res),
        res.fixedXxpCS ? "(fixed)" : ""));
}
