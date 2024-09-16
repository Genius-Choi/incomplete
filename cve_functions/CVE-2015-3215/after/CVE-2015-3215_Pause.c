bool CParaNdisTX::Pause()
{
    PNET_BUFFER_LIST NBL = nullptr;
    bool res;

    DoWithTXLock([this, &NBL, &res]()
                 {
                     NBL = RemoveAllNonWaitingNBLs();
                     res = (!m_VirtQueue.HasPacketsInHW() && m_WaitingList.IsEmpty());
                 });

    if(NBL != nullptr)
    {
        NdisMSendNetBufferListsComplete(m_Context->MiniportHandle, NBL, 0);
    }

    return res;
}
