void CNBL::StartMapping()
{
    CDpcIrqlRaiser OnDpc;

    AddRef();

    m_Buffers.ForEachDetached([this](CNB *NB)
                              {
                                  if (!NB->ScheduleBuildSGListForTx())
                                  {
                                      m_HaveFailedMappings = true;
                                      NB->MappingDone(nullptr);
                                  }
                              });

    Release();
}
