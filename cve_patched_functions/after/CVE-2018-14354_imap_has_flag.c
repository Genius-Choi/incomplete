bool imap_has_flag(struct ListHead *flag_list, const char *flag)
{
  if (STAILQ_EMPTY(flag_list))
    return false;

  struct ListNode *np;
  STAILQ_FOREACH(np, flag_list, entries)
  {
    if (mutt_str_strncasecmp(np->data, flag, strlen(np->data)) == 0)
      return true;

    if (mutt_str_strncmp(np->data, "\\*", strlen(np->data)) == 0)
      return true;
  }

  return false;
}
