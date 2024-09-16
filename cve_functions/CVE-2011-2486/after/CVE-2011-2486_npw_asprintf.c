char *npw_asprintf(const char *format, ...)
{
  va_list args;
  va_start(args, format);
  int alen = vsnprintf(NULL, 0, format, args);
  va_end(args);
  char *str = malloc(alen+1);
  if (str == NULL)
	return NULL;
  va_start(args, format);
  int rlen = vsnprintf(str, alen+1, format, args);
  va_end(args);
  if (rlen != alen) {
	free(str);
	return NULL;
  }
  return str;
}
