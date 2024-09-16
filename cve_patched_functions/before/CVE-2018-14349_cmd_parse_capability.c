static void cmd_parse_capability(struct ImapData *idata, char *s)
{
  mutt_debug(3, "Handling CAPABILITY\n");

  s = imap_next_word(s);
  char *bracket = strchr(s, ']');
  if (bracket)
    *bracket = '\0';
  FREE(&idata->capstr);
  idata->capstr = mutt_str_strdup(s);

  memset(idata->capabilities, 0, sizeof(idata->capabilities));

  while (*s)
  {
    for (int i = 0; i < CAPMAX; i++)
    {
      if (mutt_str_word_casecmp(Capabilities[i], s) == 0)
      {
        mutt_bit_set(idata->capabilities, i);
        mutt_debug(4, " Found capability \"%s\": %d\n", Capabilities[i], i);
        break;
      }
    }
    s = imap_next_word(s);
  }
}
