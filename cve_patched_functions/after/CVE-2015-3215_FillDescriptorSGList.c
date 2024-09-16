bool CNB::FillDescriptorSGList(CTXDescriptor &Descriptor, ULONG ParsedHeadersLength) const
{
    return Descriptor.SetupHeaders(ParsedHeadersLength) &&
           MapDataToVirtioSGL(Descriptor, ParsedHeadersLength + NET_BUFFER_DATA_OFFSET(m_NB));
}
