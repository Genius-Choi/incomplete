bash_glob_quote_filename (s, rtype, qcp)
     char *s;
     int rtype;
     char *qcp;
{
  if (globorig && qcp && *qcp == '\0' && STREQ (s, globorig))
    return (savestring (s));
  else
    return (bash_quote_filename (s, rtype, qcp));
}
