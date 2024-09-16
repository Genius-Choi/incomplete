inline int PacketCopyData(Packet *p, uint8_t *pktdata, uint32_t pktlen)
{
    SET_PKT_LEN(p, (size_t)pktlen);
    return PacketCopyDataOffset(p, 0, pktdata, pktlen);
}
