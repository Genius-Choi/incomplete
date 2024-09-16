safe_atou32(const char *str, uint32_t *val)
{
  char *end;
  unsigned long intval;

  *val = 0;

  errno = 0;
  intval = strtoul(str, &end, 10);

  if (((errno == ERANGE) && (intval == ULONG_MAX))
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

  if (intval > UINT32_MAX)
    {
      DPRINTF(E_DBG, L_MISC, "Integer value too large (%s)\n", str);

      return -1;
    }

  *val = (uint32_t)intval;

  return 0;
}
