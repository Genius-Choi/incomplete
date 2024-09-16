void CParaNdisTX::CancelNBLs(PVOID CancelId)
{
    auto CanceledNBLs = BuildCancelList(CancelId);
    if (CanceledNBLs != nullptr)
    {
        NdisMSendNetBufferListsComplete(m_Context->MiniportHandle, CanceledNBLs, 0);
    }
}
