CNB *CNBL::PopMappedNB()
{
    m_MappedBuffersDetached++;
    return m_MappedBuffers.Pop();
}
