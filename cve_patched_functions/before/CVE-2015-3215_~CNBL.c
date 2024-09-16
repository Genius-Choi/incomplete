CNBL::~CNBL()
{
    CDpcIrqlRaiser OnDpc;

    m_MappedBuffers.ForEachDetached([this](CNB *NB)
                                    { CNB::Destroy(NB, m_Context->MiniportHandle); });

    m_Buffers.ForEachDetached([this](CNB *NB)
                              { CNB::Destroy(NB, m_Context->MiniportHandle); });

    if(m_NBL)
    {
        auto NBL = DetachInternalObject();
        NET_BUFFER_LIST_NEXT_NBL(NBL) = nullptr;
        NdisMSendNetBufferListsComplete(m_Context->MiniportHandle, NBL, 0);
    }
}
