getChar(char *p)
{
    return wc_any_to_ucs(wtf_parse1((wc_uchar **)&p));
}
