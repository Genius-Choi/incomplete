static void burl_offset_tolower (buffer * const b, const size_t off)
{
    /*(skips over all percent-encodings, including encoding of alpha chars)*/
    for (char *p = b->ptr+off; p[0]; ++p) {
        if (p[0] >= 'A' && p[0] <= 'Z') p[0] |= 0x20;
        else if (p[0]=='%' && light_isxdigit(p[1]) && light_isxdigit(p[2]))
            p+=2;
    }
}
