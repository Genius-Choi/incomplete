safe_snprintf_cat(char *dst, size_t n, const char *fmt, ...)
{
  size_t dstlen;
  va_list va;
  int ret;

  if (!dst || !fmt)
    return -1;

  dstlen = strlen(dst);
  if (n < dstlen)
    return -1;

  va_start(va, fmt);
  ret = vsnprintf(dst + dstlen, n - dstlen, fmt, va);
  va_end(va);

  if (ret >= 0 && ret < n - dstlen)
    return 0;
  else
    return -1;
}
