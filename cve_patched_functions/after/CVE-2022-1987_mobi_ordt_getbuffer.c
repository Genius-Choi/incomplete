size_t mobi_ordt_getbuffer(const MOBIOrdt *ordt, MOBIBuffer *buf, uint16_t *offset) {
    size_t i = 0;
    if (ordt->type == 1) {
        *offset = mobi_buffer_get8(buf);
        i++;
    } else {
        *offset = mobi_buffer_get16(buf);
        i += 2;
    }
    return i;
}
