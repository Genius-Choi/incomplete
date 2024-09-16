DnsPacket *dns_packet_ref(DnsPacket *p) {

        if (!p)
                return NULL;

        assert(!p->on_stack);

        assert(p->n_ref > 0);
        p->n_ref++;
        return p;
}
