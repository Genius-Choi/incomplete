bool CNBL::ParseBuffers()
{
    m_MaxDataLength = 0;

    for (auto NB = NET_BUFFER_LIST_FIRST_NB(m_NBL); NB != nullptr; NB = NET_BUFFER_NEXT_NB(NB))
    {
        CNB *NBHolder = new (m_Context->MiniportHandle) CNB(NB, this, m_Context);
        if(!NBHolder || !NBHolder->IsValid())
        {
            return false;
        }
        RegisterNB(NBHolder);
        m_MaxDataLength = max(m_MaxDataLength, NBHolder->GetDataLength());
    }

    if(m_MaxDataLength == 0)
    {
        DPrintf(0, ("Empty NBL (%p) dropped\n", __FUNCTION__, m_NBL));
        return false;
    }

    return true;
}
