dup_array (char **arr, size_t len)
{
  size_t i;
  char **ret;

  ret = malloc (sizeof (char *) * (len + 1));
  if (ret == NULL)
    error (EXIT_FAILURE, errno, "cannot allocate memory");
  for (i = 0; i < len; i++)
    ret[i] = xstrdup (arr[i]);

  ret[i] = NULL;
  return ret;
}
