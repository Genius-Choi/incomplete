BOOLEAN ParaNdis_BindRxBufferToPacket(
    PARANDIS_ADAPTER *pContext,
    pRxNetDescriptor p)
{
    ULONG i;
    PMDL *NextMdlLinkage = &p->Holder;

    for(i = PARANDIS_FIRST_RX_DATA_PAGE; i < p->PagesAllocated; i++)
    {
        *NextMdlLinkage = NdisAllocateMdl(pContext->MiniportHandle, p->PhysicalPages[i].Virtual, PAGE_SIZE);
        if(*NextMdlLinkage == NULL) goto error_exit;

        NextMdlLinkage = &(NDIS_MDL_LINKAGE(*NextMdlLinkage));
    }
    *NextMdlLinkage = NULL;

    return TRUE;

error_exit:

    ParaNdis_UnbindRxBufferFromPacket(p);
    return FALSE;
}
