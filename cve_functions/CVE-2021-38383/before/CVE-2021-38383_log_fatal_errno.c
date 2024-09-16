log_fatal_errno(int domain, const char *func, int line)
{
  DPRINTF(E_FATAL, domain, "%s failed at line %d, error %d (%s)\n", func, line, errno, strerror(errno));
  abort();
}
