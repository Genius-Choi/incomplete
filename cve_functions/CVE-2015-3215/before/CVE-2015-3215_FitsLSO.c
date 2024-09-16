bool CNBL::FitsLSO()
{
    return (m_MaxDataLength <= PARANDIS_MAX_LSO_SIZE + LsoTcpHeaderOffset() + MAX_TCP_HEADER_SIZE);
}
