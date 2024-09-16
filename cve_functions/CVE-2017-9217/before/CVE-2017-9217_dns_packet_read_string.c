int dns_packet_read_string(DnsPacket *p, char **ret, size_t *start) {
        _cleanup_(rewind_dns_packet) DnsPacketRewinder rewinder;
        const void *d;
        char *t;
        uint8_t c;
        int r;

        assert(p);
        INIT_REWINDER(rewinder, p);

        r = dns_packet_read_uint8(p, &c, NULL);
        if (r < 0)
                return r;

        r = dns_packet_read(p, c, &d, NULL);
        if (r < 0)
                return r;

        if (memchr(d, 0, c))
                return -EBADMSG;

        t = strndup(d, c);
        if (!t)
                return -ENOMEM;

        if (!utf8_is_valid(t)) {
                free(t);
                return -EBADMSG;
        }

        *ret = t;

        if (start)
                *start = rewinder.saved_rindex;
        CANCEL_REWINDER(rewinder);

        return 0;
}
