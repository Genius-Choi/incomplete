istr_hash (gconstpointer key)
{
    const char *p;
    guint h;

    h = 0;
    for (p = key; *p != '\0'; p++)
    {
        h = (h << 5) - h + g_ascii_tolower (*p);
    }

    return h;
}
