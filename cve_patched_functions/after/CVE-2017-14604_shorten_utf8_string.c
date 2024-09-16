shorten_utf8_string (const char *base,
                     int         reduce_by_num_bytes)
{
    int len;
    char *ret;
    const char *p;

    len = strlen (base);
    len -= reduce_by_num_bytes;

    if (len <= 0)
    {
        return NULL;
    }

    ret = g_new (char, len + 1);

    p = base;
    while (len)
    {
        char *next;
        next = g_utf8_next_char (p);
        if (next - p > len || *next == '\0')
        {
            break;
        }

        len -= next - p;
        p = next;
    }

    if (p - base == 0)
    {
        g_free (ret);
        return NULL;
    }
    else
    {
        memcpy (ret, base, p - base);
        ret[p - base] = '\0';
        return ret;
    }
}
