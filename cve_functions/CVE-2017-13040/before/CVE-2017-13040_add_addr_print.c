add_addr_print(netdissect_options *ndo,
               const u_char *opt, u_int opt_len, u_char flags _U_)
{
        const struct mp_add_addr *add_addr = (const struct mp_add_addr *) opt;
        u_int ipver = MP_ADD_ADDR_IPVER(add_addr->sub_ipver);

        if (!((opt_len == 8 || opt_len == 10) && ipver == 4) &&
            !((opt_len == 20 || opt_len == 22) && ipver == 6))
                return 0;

        ND_PRINT((ndo, " id %u", add_addr->addr_id));
        switch (ipver) {
        case 4:
                ND_PRINT((ndo, " %s", ipaddr_string(ndo, add_addr->u.v4.addr)));
                if (opt_len == 10)
                        ND_PRINT((ndo, ":%u", EXTRACT_16BITS(add_addr->u.v4.port)));
                break;
        case 6:
                ND_PRINT((ndo, " %s", ip6addr_string(ndo, add_addr->u.v6.addr)));
                if (opt_len == 22)
                        ND_PRINT((ndo, ":%u", EXTRACT_16BITS(add_addr->u.v6.port)));
                break;
        default:
                return 0;
        }

        return 1;
}
