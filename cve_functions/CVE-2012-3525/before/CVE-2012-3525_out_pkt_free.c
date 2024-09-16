void out_pkt_free(pkt_t pkt)
{
    nad_free(pkt->nad);
    jid_free(pkt->from);
    jid_free(pkt->to);
    free(pkt);
}
