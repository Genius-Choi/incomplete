void dns_packet_set_flags(DnsPacket *p, bool dnssec_checking_disabled, bool truncated) {

        DnsPacketHeader *h;

        assert(p);

        h = DNS_PACKET_HEADER(p);

        switch(p->protocol) {
        case DNS_PROTOCOL_LLMNR:
                assert(!truncated);

                h->flags = htobe16(DNS_PACKET_MAKE_FLAGS(0 /* qr */,
                                                         0 /* opcode */,
                                                         0 /* c */,
                                                         0 /* tc */,
                                                         0 /* t */,
                                                         0 /* ra */,
                                                         0 /* ad */,
                                                         0 /* cd */,
                                                         0 /* rcode */));
                break;

        case DNS_PROTOCOL_MDNS:
                h->flags = htobe16(DNS_PACKET_MAKE_FLAGS(0         /* qr */,
                                                         0         /* opcode */,
                                                         0         /* aa */,
                                                         truncated /* tc */,
                                                         0         /* rd (ask for recursion) */,
                                                         0         /* ra */,
                                                         0         /* ad */,
                                                         0         /* cd */,
                                                         0         /* rcode */));
                break;

        default:
                assert(!truncated);

                h->flags = htobe16(DNS_PACKET_MAKE_FLAGS(0 /* qr */,
                                                         0 /* opcode */,
                                                         0 /* aa */,
                                                         0 /* tc */,
                                                         1 /* rd (ask for recursion) */,
                                                         0 /* ra */,
                                                         0 /* ad */,
                                                         dnssec_checking_disabled /* cd */,
                                                         0 /* rcode */));
        }
}
