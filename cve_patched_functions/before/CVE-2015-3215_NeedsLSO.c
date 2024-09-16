bool CNBL::NeedsLSO()
{
    return m_MaxDataLength > m_Context->MaxPacketSize.nMaxFullSizeOS;
}
