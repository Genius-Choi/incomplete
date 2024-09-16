log_fatal_err(int domain, const char *func, int line, int err)
{
  DPRINTF(E_FATAL, domain, "%s failed at line %d, error %d (%s)\n", func, line, err, strerror(err));
  abort();
}
