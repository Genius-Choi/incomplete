static LPCSTR __inline GetPacketCase(tTcpIpPacketParsingResult res)
{
    static const char *const IPCaseName[4] = { "not tested", "Non-IP", "IPv4", "IPv6" };
    if (res.xxpStatus == ppresXxpKnown) return res.TcpUdp == ppresIsTCP ? 
        (res.ipStatus == ppresIPV4 ? "TCPv4" : "TCPv6") : 
        (res.ipStatus == ppresIPV4 ? "UDPv4" : "UDPv6");
    if (res.xxpStatus == ppresXxpIncomplete) return res.TcpUdp == ppresIsTCP ? "Incomplete TCP" : "Incomplete UDP";
    if (res.xxpStatus == ppresXxpOther) return "IP";
    return  IPCaseName[res.ipStatus];
}
