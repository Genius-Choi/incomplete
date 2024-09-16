bool CNB::BindToDescriptor(CTXDescriptor &Descriptor)
{
    if (m_SGL == nullptr)
    {
        return false;
    }

    Descriptor.SetNB(this);

    auto &HeadersArea = Descriptor.HeadersAreaAccessor();
    auto EthHeaders = HeadersArea.EthHeadersAreaVA();
    ULONG HeadersLength;
    ULONG L4HeaderOffset;

    if (!CopyHeaders(EthHeaders, HeadersArea.MaxEthHeadersSize(), HeadersLength, L4HeaderOffset))
    {
        return false;
    }

    BuildPriorityHeader(HeadersArea.EthHeader(), HeadersArea.VlanHeader());
    PrepareOffloads(HeadersArea.VirtioHeader(),
                    HeadersArea.IPHeaders(),
                    GetDataLength() - m_Context->Offload.ipHeaderOffset,
                    L4HeaderOffset);

    return FillDescriptorSGList(Descriptor, HeadersLength);
}
