Strdup(Str s)
{
    Str n = Strnew_size(s->length);
    STR_LENGTH_CHECK(s);
    Strcopy(n, s);
    return n;
}
