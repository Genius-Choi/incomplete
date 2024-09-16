bool CNBL::ParseOffloads()
{
    if (IsLSO())
    {
        if(!ParseLSO())
        {
            return false;
        }
    }
    else if (IsIP4CSO())
    {
        if(!ParseCSO([this] () -> bool { return IsIP4CSO(); },
                     [this] () -> bool { return m_CsoInfo.Transmit.TcpChecksum; },
                     [this] () -> bool { return m_Context->Offload.flags.fTxTCPChecksum && m_Context->bOffloadv4Enabled; },
                     "TCP4 CSO"))
        {
            return false;
        }
        else if(!ParseCSO([this] () -> bool { return IsIP4CSO(); },
                          [this] () -> bool { return m_CsoInfo.Transmit.UdpChecksum; },
                          [this] () -> bool { return m_Context->Offload.flags.fTxUDPChecksum && m_Context->bOffloadv4Enabled; },
                          "UDP4 CSO"))
        {
            return false;
        }

        if(!ParseCSO([this] () -> bool { return IsIP4CSO(); },
                     [this] () -> bool { return m_CsoInfo.Transmit.IpHeaderChecksum; },
                     [this] () -> bool { return m_Context->Offload.flags.fTxIPChecksum && m_Context->bOffloadv4Enabled; },
                     "IP4 CSO"))
        {
            return false;
        }
    }
    else if (IsIP6CSO())
    {
        if(!ParseCSO([this] () -> bool { return IsIP6CSO(); },
                     [this] () -> bool { return m_CsoInfo.Transmit.TcpChecksum; },
                     [this] () -> bool { return m_Context->Offload.flags.fTxTCPv6Checksum && m_Context->bOffloadv6Enabled; },
                     "TCP6 CSO"))
        {
            return false;
        }
        else if(!ParseCSO([this] () -> bool { return IsIP6CSO(); },
                          [this] () -> bool { return m_CsoInfo.Transmit.UdpChecksum; },
                          [this] () -> bool { return m_Context->Offload.flags.fTxUDPv6Checksum && m_Context->bOffloadv6Enabled; },
                          "UDP6 CSO"))
        {
            return false;
        }
    }

    return true;
}
