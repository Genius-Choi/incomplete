void mutt_rfc2047_encode(char **pd, const char *specials, int col, const char *charsets)
{
  char *e = NULL;
  size_t elen;

  if (!Charset || !*pd)
    return;

  if (!charsets || !*charsets)
    charsets = "utf-8";

  rfc2047_encode(*pd, strlen(*pd), col, Charset, charsets, &e, &elen, specials);

  FREE(pd);
  *pd = e;
}
