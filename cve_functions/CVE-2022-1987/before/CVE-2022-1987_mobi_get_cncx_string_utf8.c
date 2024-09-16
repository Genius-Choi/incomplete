char * mobi_get_cncx_string_utf8(const MOBIPdbRecord *cncx_record, const uint32_t cncx_offset, MOBIEncoding cncx_encoding) {
    char *string = mobi_get_cncx_string(cncx_record, cncx_offset);
    if (string != NULL && cncx_encoding == MOBI_CP1252) {
        size_t in_len = strlen(string);
        size_t out_len = in_len * 3 + 1;
        char *decoded = malloc(out_len);
        if (decoded) {
            mobi_cp1252_to_utf8(decoded, string, &out_len, in_len);
            free(string);
            string = strdup(decoded);
            free(decoded);
        }
    }
    return string;
}
