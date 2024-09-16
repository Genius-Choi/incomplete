void CNBL::RegisterMappedNB(CNB *NB)
{
    if (m_MappedBuffers.PushBack(NB) == m_BuffersNumber)
    {
        m_ParentTXPath->NBLMappingDone(this);
    }
}
