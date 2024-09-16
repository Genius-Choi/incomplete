static int get_mailbox(const char *path, struct ImapData **hidata, char *buf, size_t blen)
{
  struct ImapMbox mx;

  if (imap_parse_path(path, &mx))
  {
    mutt_debug(1, "Error parsing %s\n", path);
    return -1;
  }
  if (!(*hidata = imap_conn_find(&(mx.account), ImapPassive ? MUTT_IMAP_CONN_NONEW : 0)) ||
      (*hidata)->state < IMAP_AUTHENTICATED)
  {
    FREE(&mx.mbox);
    return -1;
  }

  imap_fix_path(*hidata, mx.mbox, buf, blen);
  if (!*buf)
    mutt_str_strfcpy(buf, "INBOX", blen);
  FREE(&mx.mbox);

  return 0;
}
