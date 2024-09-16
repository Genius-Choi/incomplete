int dns_packet_append_opt(DnsPacket *p, uint16_t max_udp_size, bool edns0_do, int rcode, size_t *start) {
        size_t saved_size;
        int r;

        assert(p);
        /* we must never advertise supported packet size smaller than the legacy max */
        assert(max_udp_size >= DNS_PACKET_UNICAST_SIZE_MAX);
        assert(rcode >= 0);
        assert(rcode <= _DNS_RCODE_MAX);

        if (p->opt_start != (size_t) -1)
                return -EBUSY;

        assert(p->opt_size == (size_t) -1);

        saved_size = p->size;

        /* empty name */
        r = dns_packet_append_uint8(p, 0, NULL);
        if (r < 0)
                return r;

        /* type */
        r = dns_packet_append_uint16(p, DNS_TYPE_OPT, NULL);
        if (r < 0)
                goto fail;

        /* class: maximum udp packet that can be received */
        r = dns_packet_append_uint16(p, max_udp_size, NULL);
        if (r < 0)
                goto fail;

        /* extended RCODE and VERSION */
        r = dns_packet_append_uint16(p, ((uint16_t) rcode & 0x0FF0) << 4, NULL);
        if (r < 0)
                goto fail;

        /* flags: DNSSEC OK (DO), see RFC3225 */
        r = dns_packet_append_uint16(p, edns0_do ? EDNS0_OPT_DO : 0, NULL);
        if (r < 0)
                goto fail;

        /* RDLENGTH */
        if (edns0_do && !DNS_PACKET_QR(p)) {
                /* If DO is on and this is not a reply, also append RFC6975 Algorithm data */

                static const uint8_t rfc6975[] = {

                        0, 5, /* OPTION_CODE: DAU */
                        0, 6, /* LIST_LENGTH */
                        DNSSEC_ALGORITHM_RSASHA1,
                        DNSSEC_ALGORITHM_RSASHA1_NSEC3_SHA1,
                        DNSSEC_ALGORITHM_RSASHA256,
                        DNSSEC_ALGORITHM_RSASHA512,
                        DNSSEC_ALGORITHM_ECDSAP256SHA256,
                        DNSSEC_ALGORITHM_ECDSAP384SHA384,

                        0, 6, /* OPTION_CODE: DHU */
                        0, 3, /* LIST_LENGTH */
                        DNSSEC_DIGEST_SHA1,
                        DNSSEC_DIGEST_SHA256,
                        DNSSEC_DIGEST_SHA384,

                        0, 7, /* OPTION_CODE: N3U */
                        0, 1, /* LIST_LENGTH */
                        NSEC3_ALGORITHM_SHA1,
                };

                r = dns_packet_append_uint16(p, sizeof(rfc6975), NULL);
                if (r < 0)
                        goto fail;

                r = dns_packet_append_blob(p, rfc6975, sizeof(rfc6975), NULL);
        } else
                r = dns_packet_append_uint16(p, 0, NULL);
        if (r < 0)
                goto fail;

        DNS_PACKET_HEADER(p)->arcount = htobe16(DNS_PACKET_ARCOUNT(p) + 1);

        p->opt_start = saved_size;
        p->opt_size = p->size - saved_size;

        if (start)
                *start = saved_size;

        return 0;

fail:
        dns_packet_truncate(p, saved_size);
        return r;
}
