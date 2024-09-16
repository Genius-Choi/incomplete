static size_t encode_block(char *str, char *buf, size_t buflen, const char *fromcode,
                           const char *tocode, encoder_t encoder)
{
  if (!fromcode)
  {
    return (*encoder)(str, buf, buflen, tocode);
  }

  const iconv_t cd = mutt_ch_iconv_open(tocode, fromcode, 0);
  assert(cd != (iconv_t)(-1));
  const char *ib = buf;
  size_t ibl = buflen;
  char tmp[ENCWORD_LEN_MAX - ENCWORD_LEN_MIN + 1];
  char *ob = tmp;
  size_t obl = sizeof(tmp) - strlen(tocode);
  const size_t n1 = iconv(cd, (ICONV_CONST char **) &ib, &ibl, &ob, &obl);
  const size_t n2 = iconv(cd, NULL, NULL, &ob, &obl);
  assert(n1 != (size_t)(-1) && n2 != (size_t)(-1));
  iconv_close(cd);
  return (*encoder)(str, tmp, ob - tmp, tocode);
}
