bool CParaNdisTX::Create(PPARANDIS_ADAPTER Context, UINT DeviceQueueIndex)
{
    m_Context = Context;
    m_queueIndex = (u16)DeviceQueueIndex;

    return m_VirtQueue.Create(DeviceQueueIndex,
        m_Context->IODevice,
        m_Context->MiniportHandle,
        m_Context->bDoPublishIndices ? true : false,
        m_Context->maxFreeTxDescriptors,
        m_Context->nVirtioHeaderSize,
        m_Context);
}
