void CNB::SetupCSO(virtio_net_hdr_basic *VirtioHeader, ULONG L4HeaderOffset) const
{
    u16 PriorityHdrLen = m_ParentNBL->TCI() ? ETH_PRIORITY_HEADER_SIZE : 0;

    VirtioHeader->flags = VIRTIO_NET_HDR_F_NEEDS_CSUM;
    VirtioHeader->csum_start = static_cast<u16>(L4HeaderOffset) + PriorityHdrLen;
    VirtioHeader->csum_offset = m_ParentNBL->IsTcpCSO() ? TCP_CHECKSUM_OFFSET : UDP_CHECKSUM_OFFSET;
}
