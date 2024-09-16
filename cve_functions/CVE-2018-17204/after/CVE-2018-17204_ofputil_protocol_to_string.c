ofputil_protocol_to_string(enum ofputil_protocol protocol)
{
    const struct proto_abbrev *p;

    /* Use a "switch" statement for single-bit names so that we get a compiler
     * warning if we forget any. */
    switch (protocol) {
    case OFPUTIL_P_OF10_NXM:
        return "NXM-table_id";

    case OFPUTIL_P_OF10_NXM_TID:
        return "NXM+table_id";

    case OFPUTIL_P_OF10_STD:
        return "OpenFlow10-table_id";

    case OFPUTIL_P_OF10_STD_TID:
        return "OpenFlow10+table_id";

    case OFPUTIL_P_OF11_STD:
        return "OpenFlow11";

    case OFPUTIL_P_OF12_OXM:
        return "OXM-OpenFlow12";

    case OFPUTIL_P_OF13_OXM:
        return "OXM-OpenFlow13";

    case OFPUTIL_P_OF14_OXM:
        return "OXM-OpenFlow14";

    case OFPUTIL_P_OF15_OXM:
        return "OXM-OpenFlow15";

    case OFPUTIL_P_OF16_OXM:
        return "OXM-OpenFlow16";
    }

    /* Check abbreviations. */
    for (p = proto_abbrevs; p < &proto_abbrevs[N_PROTO_ABBREVS]; p++) {
        if (protocol == p->protocol) {
            return p->name;
        }
    }

    return NULL;
}
