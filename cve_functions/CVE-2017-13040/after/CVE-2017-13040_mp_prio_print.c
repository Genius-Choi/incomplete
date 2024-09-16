mp_prio_print(netdissect_options *ndo,
              const u_char *opt, u_int opt_len, u_char flags _U_)
{
        const struct mp_prio *mpp = (const struct mp_prio *) opt;

        if (opt_len != 3 && opt_len != 4)
                return 0;

        if (mpp->sub_b & MP_PRIO_B)
                ND_PRINT((ndo, " backup"));
        else
                ND_PRINT((ndo, " non-backup"));
        if (opt_len == 4)
                ND_PRINT((ndo, " id %u", mpp->addr_id));

        return 1;
}
