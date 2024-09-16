static void DebugParseOffloadBits()
{
    NDIS_TCP_IP_CHECKSUM_NET_BUFFER_LIST_INFO info;
    tChecksumCheckResult res;
    ULONG val = 1;
    int level = 1;
    while (val)
    {
        info.Value = (PVOID)(ULONG_PTR)val;
        if (info.Receive.IpChecksumFailed) DPrintf(level, ("W.%X=IPCS failed\n", val));
        if (info.Receive.IpChecksumSucceeded) DPrintf(level, ("W.%X=IPCS OK\n", val));
        if (info.Receive.TcpChecksumFailed) DPrintf(level, ("W.%X=TCPCS failed\n", val));
        if (info.Receive.TcpChecksumSucceeded) DPrintf(level, ("W.%X=TCPCS OK\n", val));
        if (info.Receive.UdpChecksumFailed) DPrintf(level, ("W.%X=UDPCS failed\n", val));
        if (info.Receive.UdpChecksumSucceeded) DPrintf(level, ("W.%X=UDPCS OK\n", val));
        val = val << 1;
    }
    val = 1;
    while (val)
    {
        res.value = val;
        if (res.flags.IpFailed) DPrintf(level, ("C.%X=IPCS failed\n", val));
        if (res.flags.IpOK) DPrintf(level, ("C.%X=IPCS OK\n", val));
        if (res.flags.TcpFailed) DPrintf(level, ("C.%X=TCPCS failed\n", val));
        if (res.flags.TcpOK) DPrintf(level, ("C.%X=TCPCS OK\n", val));
        if (res.flags.UdpFailed) DPrintf(level, ("C.%X=UDPCS failed\n", val));
        if (res.flags.UdpOK) DPrintf(level, ("C.%X=UDPCS OK\n", val));
        val = val << 1;
    }
}
