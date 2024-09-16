bool CNBL::ParseLSO()
{
    ASSERT(IsLSO());

    if (m_LsoInfo.LsoV1Transmit.Type != NDIS_TCP_LARGE_SEND_OFFLOAD_V1_TYPE &&
        m_LsoInfo.LsoV2Transmit.Type != NDIS_TCP_LARGE_SEND_OFFLOAD_V2_TYPE)
    {
        return false;
    }

    if (NeedsLSO() &&
        (!m_LsoInfo.LsoV2Transmit.MSS ||
         !m_LsoInfo.LsoV2Transmit.TcpHeaderOffset))
    {
        return false;
    }

    if (!FitsLSO())
    {
        return false;
    }

    if (!LsoTcpHeaderOffset() != !MSS())
    {
        return false;
    }

    if ((!m_Context->Offload.flags.fTxLso || !m_Context->bOffloadv4Enabled) &&
        m_LsoInfo.LsoV2Transmit.IPVersion == NDIS_TCP_LARGE_SEND_OFFLOAD_IPv4)
    {
        return false;
    }

    if (m_LsoInfo.LsoV2Transmit.Type == NDIS_TCP_LARGE_SEND_OFFLOAD_V2_TYPE &&
        m_LsoInfo.LsoV2Transmit.IPVersion == NDIS_TCP_LARGE_SEND_OFFLOAD_IPv6 &&
        (!m_Context->Offload.flags.fTxLsov6 || !m_Context->bOffloadv6Enabled))
    {
        return false;
    }

    return true;
}
