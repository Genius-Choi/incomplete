ofputil_encode_table_mod(const struct ofputil_table_mod *tm,
                        enum ofputil_protocol protocol)
{
    enum ofp_version ofp_version = ofputil_protocol_to_ofp_version(protocol);
    struct ofpbuf *b;

    switch (ofp_version) {
    case OFP10_VERSION: {
        ovs_fatal(0, "table mod needs OpenFlow 1.1 or later "
                     "(\'-O OpenFlow11\')");
        break;
    }
    case OFP11_VERSION:
    case OFP12_VERSION:
    case OFP13_VERSION: {
        struct ofp11_table_mod *otm;

        b = ofpraw_alloc(OFPRAW_OFPT11_TABLE_MOD, ofp_version, 0);
        otm = ofpbuf_put_zeros(b, sizeof *otm);
        otm->table_id = tm->table_id;
        otm->config = ofputil_encode_table_config(tm->miss, tm->eviction,
                                                  tm->vacancy, ofp_version);
        break;
    }
    case OFP14_VERSION:
    case OFP15_VERSION:
    case OFP16_VERSION: {
        struct ofp14_table_mod *otm;

        b = ofpraw_alloc(OFPRAW_OFPT14_TABLE_MOD, ofp_version, 0);
        otm = ofpbuf_put_zeros(b, sizeof *otm);
        otm->table_id = tm->table_id;
        otm->config = ofputil_encode_table_config(tm->miss, tm->eviction,
                                                  tm->vacancy, ofp_version);

        if (tm->eviction_flags != UINT32_MAX) {
            ofpprop_put_u32(b, OFPTMPT14_EVICTION, tm->eviction_flags);
        }
        if (tm->vacancy == OFPUTIL_TABLE_VACANCY_ON) {
            struct ofp14_table_mod_prop_vacancy *otv;

            otv = ofpprop_put_zeros(b, OFPTMPT14_VACANCY, sizeof *otv);
            otv->vacancy_down = tm->table_vacancy.vacancy_down;
            otv->vacancy_up = tm->table_vacancy.vacancy_up;
        }
        break;
    }
    default:
        OVS_NOT_REACHED();
    }

    return b;
}
