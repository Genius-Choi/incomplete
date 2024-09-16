CNB::~CNB()
{
    ASSERT(KeGetCurrentIrql() == DISPATCH_LEVEL);

    if(m_SGL != nullptr)
    {
        NdisMFreeNetBufferSGList(m_Context->DmaHandle, m_SGL, m_NB);
    }
}
