dump_pdu(const char *type, void *buffer, unsigned long length)
{
    unsigned char
       *p;
    int
        position = 0;
    OFOStringStream
        str;

    str << "PDU Type: " << type << ", PDU Length: " << length-6 << " + 6 bytes PDU header" << OFendl;
    if (length > 512) {
        str << "Only dumping 512 bytes." << OFendl;
        length = 512;
    }
    p = (unsigned char*)buffer;

    while (length-- > 0) {
        str << "  "
            << STD_NAMESPACE hex << STD_NAMESPACE setfill('0') << STD_NAMESPACE setw(2) << ((unsigned int)(*p++))
            << STD_NAMESPACE dec;
        if ((++position) % 16 == 0) str << OFendl;
    }
    str << OFStringStream_ends;
    OFSTRINGSTREAM_GETOFSTRING(str, ret)
    return ret;
}
