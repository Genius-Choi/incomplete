ofputil_versions_from_string(const char *s)
{
    size_t i = 0;
    uint32_t bitmap = 0;

    while (s[i]) {
        size_t j;
        int version;
        char *key;

        if (is_delimiter(s[i])) {
            i++;
            continue;
        }
        j = 0;
        while (s[i + j] && !is_delimiter(s[i + j])) {
            j++;
        }
        key = xmemdup0(s + i, j);
        version = ofputil_version_from_string(key);
        if (!version) {
            VLOG_FATAL("Unknown OpenFlow version: \"%s\"", key);
        }
        free(key);
        bitmap |= 1u << version;
        i += j;
    }

    return bitmap;
}
