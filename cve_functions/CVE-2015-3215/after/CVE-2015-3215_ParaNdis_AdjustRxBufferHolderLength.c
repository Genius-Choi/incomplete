void ParaNdis_AdjustRxBufferHolderLength(
    pRxNetDescriptor p,
    ULONG ulDataOffset)
{
    PMDL NextMdlLinkage = p->Holder;
    ULONG ulBytesLeft = p->PacketInfo.dataLength + ulDataOffset;

    while(NextMdlLinkage != NULL)
    {
        ULONG ulThisMdlBytes = min(PAGE_SIZE, ulBytesLeft);
        NdisAdjustMdlLength(NextMdlLinkage, ulThisMdlBytes);
        ulBytesLeft -= ulThisMdlBytes;
        NextMdlLinkage = NDIS_MDL_LINKAGE(NextMdlLinkage);
    }
    ASSERT(ulBytesLeft == 0);
}
