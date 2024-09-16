remove_addr_print(netdissect_options *ndo,
                  const u_char *opt, u_int opt_len, u_char flags _U_)
{
        const struct mp_remove_addr *remove_addr = (const struct mp_remove_addr *) opt;
        const uint8_t *addr_id = &remove_addr->addrs_id;

        if (opt_len < 4)
                return 0;

        opt_len -= 3;
        ND_PRINT((ndo, " id"));
        while (opt_len--)
                ND_PRINT((ndo, " %u", *addr_id++));
        return 1;
}
