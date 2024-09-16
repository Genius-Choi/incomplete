bool CNB::Copy(PVOID Dst, ULONG Length) const
{
    ULONG CurrOffset = NET_BUFFER_CURRENT_MDL_OFFSET(m_NB);
    ULONG Copied = 0;

    for (PMDL CurrMDL = NET_BUFFER_CURRENT_MDL(m_NB);
         CurrMDL != nullptr && Copied < Length;
         CurrMDL = CurrMDL->Next)
    {
        ULONG CurrLen;
        PVOID CurrAddr;

#if NDIS_SUPPORT_NDIS620
        NdisQueryMdl(CurrMDL, &CurrAddr, &CurrLen, LowPagePriority | MdlMappingNoExecute);
#else
        NdisQueryMdl(CurrMDL, &CurrAddr, &CurrLen, LowPagePriority);
#endif

        if (CurrAddr == nullptr)
        {
            break;
        }

        CurrLen = min(CurrLen - CurrOffset, Length - Copied);

        NdisMoveMemory(RtlOffsetToPointer(Dst, Copied),
                       RtlOffsetToPointer(CurrAddr, CurrOffset),
                       CurrLen);

        Copied += CurrLen;
        CurrOffset = 0;
    }

    return (Copied == Length);
}
