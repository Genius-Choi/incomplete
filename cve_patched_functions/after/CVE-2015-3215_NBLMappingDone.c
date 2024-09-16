void CParaNdisTX::NBLMappingDone(CNBL *NBLHolder)
{
    ASSERT(KeGetCurrentIrql() == DISPATCH_LEVEL);

    if (NBLHolder->MappingSuceeded())
    {
        DoWithTXLock([NBLHolder, this](){ m_SendList.PushBack(NBLHolder); });
        DoPendingTasks(false);
    }
    else
    {
        NBLHolder->SetStatus(NDIS_STATUS_FAILURE);
        NBLHolder->Release();
    }
}
