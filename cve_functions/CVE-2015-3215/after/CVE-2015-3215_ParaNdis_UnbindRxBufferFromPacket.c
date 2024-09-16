void ParaNdis_UnbindRxBufferFromPacket(
    pRxNetDescriptor p)
{
    PMDL NextMdlLinkage = p->Holder;

    while(NextMdlLinkage != NULL)
    {
        PMDL pThisMDL = NextMdlLinkage;
        NextMdlLinkage = NDIS_MDL_LINKAGE(pThisMDL);

        NdisAdjustMdlLength(pThisMDL, PAGE_SIZE);
        NdisFreeMdl(pThisMDL);
    }
}
