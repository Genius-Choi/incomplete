b64_encode(const uint8_t *src, int srclen)
{
  char *out;
  int len;
  char *ret;

  len = AV_BASE64_SIZE(srclen);

  CHECK_NULL(L_MISC, out = calloc(1, len));

  ret = av_base64_encode(out, len, src, srclen);
  if (!ret)
    {
      free(out);
      return NULL;
    }

  return out;
}
