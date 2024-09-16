uint16_t mobi_ordt_lookup(const MOBIOrdt *ordt, const uint16_t offset) {
    uint16_t utf16;
    if (offset < ordt->offsets_count) {
        utf16 = ordt->ordt2[offset];
    } else {
        utf16 = offset;
    }
    return utf16;
}
