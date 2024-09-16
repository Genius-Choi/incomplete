CNBL::CNBL(PNET_BUFFER_LIST NBL, PPARANDIS_ADAPTER Context, CParaNdisTX &ParentTXPath)
    : m_NBL(NBL)
    , m_Context(Context)
    , m_ParentTXPath(&ParentTXPath)
{
    m_NBL->Scratch = this;
    m_LsoInfo.Value = NET_BUFFER_LIST_INFO(m_NBL, TcpLargeSendNetBufferListInfo);
    m_CsoInfo.Value = NET_BUFFER_LIST_INFO(m_NBL, TcpIpChecksumNetBufferListInfo);
}
