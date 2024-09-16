void CNB::BuildPriorityHeader(PETH_HEADER EthHeader, PVLAN_HEADER VlanHeader) const
{
    VlanHeader->TCI = RtlUshortByteSwap(m_ParentNBL->TCI());

    if (VlanHeader->TCI != 0)
    {
        VlanHeader->EthType = EthHeader->EthType;
        EthHeader->EthType = RtlUshortByteSwap(PRIO_HEADER_ETH_TYPE);
    }
}
