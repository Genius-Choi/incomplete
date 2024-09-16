const char *imap_cmd_trailer(struct ImapData *idata)
{
  static const char *notrailer = "";
  const char *s = idata->buf;

  if (!s)
  {
    mutt_debug(2, "not a tagged response\n");
    return notrailer;
  }

  s = imap_next_word((char *) s);
  if (!s || ((mutt_str_strncasecmp(s, "OK", 2) != 0) &&
             (mutt_str_strncasecmp(s, "NO", 2) != 0) &&
             (mutt_str_strncasecmp(s, "BAD", 3) != 0)))
  {
    mutt_debug(2, "not a command completion: %s\n", idata->buf);
    return notrailer;
  }

  s = imap_next_word((char *) s);
  if (!s)
    return notrailer;

  return s;
}
