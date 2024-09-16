PNET_BUFFER_LIST CParaNdisTX::BuildCancelList(PVOID CancelId)
{
    PNET_BUFFER_LIST CanceledNBLs = nullptr;
    TSpinLocker LockedContext(m_Lock);

    m_SendList.ForEachDetachedIf([CancelId](CNBL* NBL){ return NBL->MatchCancelID(CancelId) && !NBL->HaveDetachedBuffers(); },
                                     [this, &CanceledNBLs](CNBL* NBL)
                                     {
                                         NBL->SetStatus(NDIS_STATUS_SEND_ABORTED);
                                         auto RawNBL = NBL->DetachInternalObject();
                                         NBL->Release();
                                         NET_BUFFER_LIST_NEXT_NBL(RawNBL) = CanceledNBLs;
                                         CanceledNBLs = RawNBL;
                                     });

    return CanceledNBLs;
}
