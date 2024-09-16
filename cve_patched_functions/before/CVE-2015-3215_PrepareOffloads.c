void CNB::PrepareOffloads(virtio_net_hdr_basic *VirtioHeader, PVOID IpHeader, ULONG EthPayloadLength, ULONG L4HeaderOffset) const
{
    *VirtioHeader = {};

    if (m_ParentNBL->IsLSO())
    {
        SetupLSO(VirtioHeader, IpHeader, EthPayloadLength);
    }
    else if (m_ParentNBL->IsTcpCSO() || m_ParentNBL->IsUdpCSO())
    {
        SetupCSO(VirtioHeader, L4HeaderOffset);
    }

    if (m_ParentNBL->IsIPHdrCSO())
    {
        DoIPHdrCSO(IpHeader, EthPayloadLength);
    }
}
