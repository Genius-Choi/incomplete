safe_asprintf(const char *fmt, ...)
{
  char *ret = NULL;
  va_list va;

  va_start(va, fmt);
  if (vasprintf(&ret, fmt, va) < 0)
    {
      DPRINTF(E_FATAL, L_MISC, "Out of memory for safe_asprintf\n");
      abort();
    }
  va_end(va);

  return ret;
}
