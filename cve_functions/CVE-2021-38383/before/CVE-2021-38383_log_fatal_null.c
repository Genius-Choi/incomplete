log_fatal_null(int domain, const char *func, int line)
{
  DPRINTF(E_FATAL, domain, "%s returned NULL at line %d\n", func, line);
  abort();
}
