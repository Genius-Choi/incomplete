ULONG ParaNdis_StripVlanHeaderMoveHead(PNET_PACKET_INFO packetInfo)
{
    PUINT32 pData = (PUINT32) packetInfo->headersBuffer;

    ASSERT(packetInfo->hasVlanHeader);
    ASSERT(packetInfo->L2HdrLen == ETH_HEADER_SIZE + ETH_PRIORITY_HEADER_SIZE);

    pData[3] = pData[2];
    pData[2] = pData[1];
    pData[1] = pData[0];

    packetInfo->headersBuffer = RtlOffsetToPointer(packetInfo->headersBuffer, ETH_PRIORITY_HEADER_SIZE);
    packetInfo->dataLength -= ETH_PRIORITY_HEADER_SIZE;
    packetInfo->L2HdrLen = ETH_HEADER_SIZE;

    packetInfo->ethDestAddr = (PUCHAR) RtlOffsetToPointer(packetInfo->ethDestAddr, ETH_PRIORITY_HEADER_SIZE);
    packetInfo->ip6DestAddrOffset -= ETH_PRIORITY_HEADER_SIZE;
    packetInfo->ip6HomeAddrOffset -= ETH_PRIORITY_HEADER_SIZE;

    return ETH_PRIORITY_HEADER_SIZE;
};
