int dns_packet_append_key(DnsPacket *p, const DnsResourceKey *k, const DnsAnswerFlags flags, size_t *start) {
        size_t saved_size;
        uint16_t class;
        int r;

        assert(p);
        assert(k);

        saved_size = p->size;

        r = dns_packet_append_name(p, dns_resource_key_name(k), true, true, NULL);
        if (r < 0)
                goto fail;

        r = dns_packet_append_uint16(p, k->type, NULL);
        if (r < 0)
                goto fail;

        class = flags & DNS_ANSWER_CACHE_FLUSH ? k->class | MDNS_RR_CACHE_FLUSH : k->class;
        r = dns_packet_append_uint16(p, class, NULL);
        if (r < 0)
                goto fail;

        if (start)
                *start = saved_size;

        return 0;

fail:
        dns_packet_truncate(p, saved_size);
        return r;
}
