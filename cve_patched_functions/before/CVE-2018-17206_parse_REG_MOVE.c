parse_REG_MOVE(const char *arg, struct ofpbuf *ofpacts,
               enum ofputil_protocol *usable_protocols OVS_UNUSED)
{
    struct ofpact_reg_move *move = ofpact_put_REG_MOVE(ofpacts);
    return nxm_parse_reg_move(move, arg);
}
