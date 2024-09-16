static void cmd_parse_enabled(struct ImapData *idata, const char *s)
{
  mutt_debug(2, "Handling ENABLED\n");

  while ((s = imap_next_word((char *) s)) && *s != '\0')
  {
    if ((mutt_str_strncasecmp(s, "UTF8=ACCEPT", 11) == 0) ||
        (mutt_str_strncasecmp(s, "UTF8=ONLY", 9) == 0))
    {
      idata->unicode = 1;
    }
  }
}
