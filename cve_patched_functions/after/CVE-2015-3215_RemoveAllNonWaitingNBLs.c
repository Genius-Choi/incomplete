PNET_BUFFER_LIST CParaNdisTX::RemoveAllNonWaitingNBLs()
{
    PNET_BUFFER_LIST RemovedNBLs = nullptr;
    auto status = ParaNdis_ExactSendFailureStatus(m_Context);

    m_SendList.ForEachDetachedIf([](CNBL *NBL) { return !NBL->HaveDetachedBuffers(); },
                                     [&](CNBL *NBL)
                                     {
                                         NBL->SetStatus(status);
                                         auto RawNBL = NBL->DetachInternalObject();
                                         NBL->Release();
                                         NET_BUFFER_LIST_NEXT_NBL(RawNBL) = RemovedNBLs;
                                         RemovedNBLs = RawNBL;
                                     });

    m_SendList.ForEach([](CNBL *NBL) { NBL->CompleteMappedBuffers(); });

    return RemovedNBLs;
}
