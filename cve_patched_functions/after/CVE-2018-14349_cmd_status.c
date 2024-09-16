static int cmd_status(const char *s)
{
  s = imap_next_word((char *) s);

  if (mutt_str_strncasecmp("OK", s, 2) == 0)
    return IMAP_CMD_OK;
  if (mutt_str_strncasecmp("NO", s, 2) == 0)
    return IMAP_CMD_NO;

  return IMAP_CMD_BAD;
}
