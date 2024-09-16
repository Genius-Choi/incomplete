bool CParaNdisTX::DoPendingTasks(bool IsInterrupt)
{
    ONPAUSECOMPLETEPROC CallbackToCall = nullptr;
    PNET_BUFFER_LIST pNBLFailNow = nullptr;
    PNET_BUFFER_LIST pNBLReturnNow = nullptr;
    bool bDoKick = false;

    DoWithTXLock([&] ()
                 {
                    m_VirtQueue.ProcessTXCompletions();
                    bDoKick = SendMapped(IsInterrupt, pNBLFailNow);
                    pNBLReturnNow = ProcessWaitingList();
                    {
                        CNdisPassiveWriteAutoLock tLock(m_Context->m_PauseLock);

                        if (!m_VirtQueue.HasPacketsInHW() && m_Context->SendState == srsPausing)
                        {
                            CallbackToCall = m_Context->SendPauseCompletionProc;
                            m_Context->SendPauseCompletionProc = nullptr;
                            m_Context->SendState = srsDisabled;
                        }
                    }
                 });

    if (pNBLFailNow)
    {
        NdisMSendNetBufferListsComplete(m_Context->MiniportHandle, pNBLFailNow,
                                        NDIS_SEND_COMPLETE_FLAGS_DISPATCH_LEVEL);
    }

    if (pNBLReturnNow)
    {
        NdisMSendNetBufferListsComplete(m_Context->MiniportHandle, pNBLReturnNow,
                                        NDIS_SEND_COMPLETE_FLAGS_DISPATCH_LEVEL);
    }

    if (CallbackToCall != nullptr)
    {
        CallbackToCall(m_Context);
    }

    return bDoKick;
}
