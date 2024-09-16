name_is_acceptable (name)
     const char *name;
{
  struct ign *p;
  int nlen;

  for (nlen = strlen (name), p = fignore.ignores; p->val; p++)
    {
      if (nlen > p->len && p->len > 0 && STREQ (p->val, &name[nlen - p->len]))
	return (0);
    }

  return (1);
}
