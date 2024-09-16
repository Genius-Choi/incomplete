PNET_BUFFER_LIST CParaNdisTX::ProcessWaitingList()
{
    PNET_BUFFER_LIST CompletedNBLs = nullptr;


    m_WaitingList.ForEachDetachedIf([](CNBL* NBL) { return NBL->IsSendDone(); },
                                        [&](CNBL* NBL)
                                        {
                                            NBL->SetStatus(NDIS_STATUS_SUCCESS);
                                            auto RawNBL = NBL->DetachInternalObject();
                                            NBL->Release();
                                            NET_BUFFER_LIST_NEXT_NBL(RawNBL) = CompletedNBLs;
                                            CompletedNBLs = RawNBL;
                                        });

    return CompletedNBLs;
}
