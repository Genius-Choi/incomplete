bool CNB::MapDataToVirtioSGL(CTXDescriptor &Descriptor, ULONG Offset) const
{
    for (ULONG i = 0; i < m_SGL->NumberOfElements; i++)
    {
        if (Offset < m_SGL->Elements[i].Length)
        {
            PHYSICAL_ADDRESS PA;
            PA.QuadPart = m_SGL->Elements[i].Address.QuadPart + Offset;

            if (!Descriptor.AddDataChunk(PA, m_SGL->Elements[i].Length - Offset))
            {
                return false;
            }

            Offset = 0;
        }
        else
        {
            Offset -= m_SGL->Elements[i].Length;
        }
    }

    return true;
}
