void PacketFree(Packet *p)
{
    PACKET_DESTRUCTOR(p);
    SCFree(p);
}
