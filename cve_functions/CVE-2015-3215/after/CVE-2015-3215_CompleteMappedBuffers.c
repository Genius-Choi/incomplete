void CNBL::CompleteMappedBuffers()
{
    m_MappedBuffers.ForEachDetached([this](CNB *NB)
                                        {
                                            NBComplete();
                                            CNB::Destroy(NB, m_Context->MiniportHandle);
                                        });
}
