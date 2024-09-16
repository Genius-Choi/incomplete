static void cmd_parse_search(struct ImapData *idata, const char *s)
{
  unsigned int uid;
  struct Header *h = NULL;

  mutt_debug(2, "Handling SEARCH\n");

  while ((s = imap_next_word((char *) s)) && *s != '\0')
  {
    if (mutt_str_atoui(s, &uid) < 0)
      continue;
    h = (struct Header *) mutt_hash_int_find(idata->uid_hash, uid);
    if (h)
      h->matched = true;
  }
}
