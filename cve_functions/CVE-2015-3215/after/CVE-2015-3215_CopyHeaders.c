bool CNB::CopyHeaders(PVOID Destination, ULONG MaxSize, ULONG &HeadersLength, ULONG &L4HeaderOffset) const
{
    HeadersLength = 0;
    L4HeaderOffset = 0;

    if (m_ParentNBL->IsLSO() || m_ParentNBL->IsTcpCSO())
    {
        L4HeaderOffset = m_ParentNBL->TCPHeaderOffset();
        HeadersLength = L4HeaderOffset + sizeof(TCPHeader);
        Copy(Destination, HeadersLength);
    }
    else if (m_ParentNBL->IsUdpCSO())
    {
        Copy(Destination, MaxSize);
        L4HeaderOffset = QueryL4HeaderOffset(Destination, m_Context->Offload.ipHeaderOffset);
        HeadersLength = L4HeaderOffset + sizeof(UDPHeader);
    }
    else if (m_ParentNBL->IsIPHdrCSO())
    {
        Copy(Destination, MaxSize);
        HeadersLength = QueryL4HeaderOffset(Destination, m_Context->Offload.ipHeaderOffset);
        L4HeaderOffset = HeadersLength;
    }
    else
    {
        HeadersLength = ETH_HEADER_SIZE;
        Copy(Destination, HeadersLength);
    }

    return (HeadersLength <= MaxSize);
}
