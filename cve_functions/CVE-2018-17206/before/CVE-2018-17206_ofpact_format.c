ofpact_format(const struct ofpact *a, struct ds *s)
{
    switch (a->type) {
#define OFPACT(ENUM, STRUCT, MEMBER, NAME)                              \
        case OFPACT_##ENUM:                                             \
            format_##ENUM(ALIGNED_CAST(const struct STRUCT *, a), s);   \
            break;
        OFPACTS
#undef OFPACT
    default:
        OVS_NOT_REACHED();
    }
}
