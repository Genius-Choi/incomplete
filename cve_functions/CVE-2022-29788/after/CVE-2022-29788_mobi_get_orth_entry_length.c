uint32_t mobi_get_orth_entry_length(const MOBIIndexEntry *entry) {

    uint32_t entry_textlen;
    MOBI_RET ret = mobi_get_indxentry_tagvalue(&entry_textlen, entry, INDX_TAG_ORTH_LENGTH);
    if (ret != MOBI_SUCCESS) {
        return MOBI_NOTSET;
    }

    return entry_textlen;
}
