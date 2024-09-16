void CNBL::PushMappedNB(CNB *NB)
{
    m_MappedBuffersDetached--;
    m_MappedBuffers.Push(NB);
}
