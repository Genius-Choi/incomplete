static int StreamTcpTest40(void)
{
    uint8_t raw_vlan[] = {
        0x00, 0x20, 0x08, 0x00, 0x45, 0x00, 0x00, 0x34,
        0x3b, 0x36, 0x40, 0x00, 0x40, 0x06, 0xb7, 0xc9,
        0x83, 0x97, 0x20, 0x81, 0x83, 0x97, 0x20, 0x15,
        0x04, 0x8a, 0x17, 0x70, 0x4e, 0x14, 0xdf, 0x55,
        0x4d, 0x3d, 0x5a, 0x61, 0x80, 0x10, 0x6b, 0x50,
        0x3c, 0x4c, 0x00, 0x00, 0x01, 0x01, 0x08, 0x0a,
        0x00, 0x04, 0xf0, 0xc8, 0x01, 0x99, 0xa3, 0xf3
    };
    Packet *p = SCMalloc(SIZE_OF_PACKET);
    FAIL_IF(unlikely(p == NULL));
    ThreadVars tv;
    DecodeThreadVars dtv;

    memset(&tv, 0, sizeof(ThreadVars));
    memset(p, 0, SIZE_OF_PACKET);
    PACKET_INITIALIZE(p);

    SET_PKT_LEN(p, sizeof(raw_vlan));
    memcpy(GET_PKT_DATA(p), raw_vlan, sizeof(raw_vlan));
    memset(&dtv, 0, sizeof(DecodeThreadVars));

    FlowInitConfig(FLOW_QUIET);

    DecodeVLAN(&tv, &dtv, p, GET_PKT_DATA(p), GET_PKT_LEN(p), NULL);

    FAIL_IF(p->vlanh[0] == NULL);

    FAIL_IF(p->tcph == NULL);

    Packet *np = StreamTcpPseudoSetup(p, GET_PKT_DATA(p), GET_PKT_LEN(p));
    FAIL_IF(np == NULL);

    StreamTcpPseudoPacketSetupHeader(np,p);

    FAIL_IF(((uint8_t *)p->tcph - (uint8_t *)p->ip4h) != ((uint8_t *)np->tcph - (uint8_t *)np->ip4h));

    PACKET_DESTRUCTOR(np);
    PACKET_DESTRUCTOR(p);
    FlowShutdown();
    PacketFree(np);
    PacketFree(p);
    PASS;
}
