void npw_perror(const char *prefix, int error)
{
  if (prefix && *prefix)
	npw_printf("ERROR: %s: %s\n", prefix, npw_strerror(error));
  else
	npw_printf("ERROR: %s\n", npw_strerror(error));
}
