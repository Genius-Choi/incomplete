int asprintf(char **strp, const char *fmt, ...) {
  va_list ap;
  int len;

  *strp = MG_MALLOC(BUFSIZ);
  if (*strp == NULL) return -1;

  va_start(ap, fmt);
  len = vsnprintf(*strp, BUFSIZ, fmt, ap);
  va_end(ap);

  if (len > 0) {
    *strp = MG_REALLOC(*strp, len + 1);
    if (*strp == NULL) return -1;
  }

  if (len >= BUFSIZ) {
    va_start(ap, fmt);
    len = vsnprintf(*strp, len + 1, fmt, ap);
    va_end(ap);
  }

  return len;
}
