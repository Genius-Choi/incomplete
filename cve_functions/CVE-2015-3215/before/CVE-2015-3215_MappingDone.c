void CNB::MappingDone(PSCATTER_GATHER_LIST SGL)
{
    m_SGL = SGL;
    m_ParentNBL->RegisterMappedNB(this);
}
