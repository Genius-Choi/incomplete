BOOLEAN AnalyzeIP6DestinationExtension(
    PVOID destHdr,
    ULONG dataLength,
    IPV6_ADDRESS **homeAddr)
{
    while(dataLength != 0)
    {
        PIP6_EXT_HDR_OPTION optHdr = (PIP6_EXT_HDR_OPTION) destHdr;
        ULONG optionLen;

        switch(optHdr->Type)
        {
        case IP6_EXT_HDR_OPTION_HOME_ADDR:
            if(dataLength < sizeof(IP6_EXT_HDR_OPTION))
                return FALSE;

            optionLen = optHdr->Length + sizeof(IP6_EXT_HDR_OPTION);
            if(optHdr->Length != sizeof(IPV6_ADDRESS))
                return FALSE;

            *homeAddr = (IPV6_ADDRESS*) RtlOffsetToPointer(optHdr, sizeof(IP6_EXT_HDR_OPTION));
            break;

        case IP6_EXT_HDR_OPTION_PAD1:
            optionLen = RTL_SIZEOF_THROUGH_FIELD(IP6_EXT_HDR_OPTION, Type);
            break;

        default:
            if(dataLength < sizeof(IP6_EXT_HDR_OPTION))
                return FALSE;

            optionLen = optHdr->Length + sizeof(IP6_EXT_HDR_OPTION);
            break;
        }

        destHdr = RtlOffsetToPointer(destHdr, optionLen);
        if(dataLength < optionLen)
            return FALSE;

        dataLength -= optionLen;
    }

    return TRUE;
}
