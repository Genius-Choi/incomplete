ofpacts_parse(char *str, struct ofpbuf *ofpacts,
              enum ofputil_protocol *usable_protocols, bool allow_instructions,
              enum ofpact_type outer_action)
{
    uint32_t orig_size = ofpacts->size;
    char *error = ofpacts_parse__(str, ofpacts, usable_protocols,
                                  allow_instructions, outer_action);
    if (error) {
        ofpacts->size = orig_size;
    }
    return error;
}
