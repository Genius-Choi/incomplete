safe_atou64(const char *str, uint64_t *val)
{
  char *end;
  unsigned long long intval;

  *val = 0;

  errno = 0;
  intval = strtoull(str, &end, 10);

  if (((errno == ERANGE) && (intval == ULLONG_MAX))
      || ((errno != 0) && (intval == 0)))
    {
      DPRINTF(E_DBG, L_MISC, "Invalid integer in string (%s): %s\n", str, strerror(errno));

      return -1;
    }

  if (end == str)
    {
      DPRINTF(E_DBG, L_MISC, "No integer found in string (%s)\n", str);

      return -1;
    }

  if (intval > UINT64_MAX)
    {
      DPRINTF(E_DBG, L_MISC, "Integer value too large (%s)\n", str);

      return -1;
    }

  *val = (uint64_t)intval;

  return 0;
}
