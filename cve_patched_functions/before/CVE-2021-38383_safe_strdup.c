safe_strdup(const char *str)
{
  if (str == NULL)
    return NULL;

  return strdup(str);
}
