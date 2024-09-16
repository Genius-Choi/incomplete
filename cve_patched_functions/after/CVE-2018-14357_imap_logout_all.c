void imap_logout_all(void)
{
  struct ConnectionList *head = mutt_socket_head();
  struct Connection *np, *tmp;
  TAILQ_FOREACH_SAFE(np, head, entries, tmp)
  {
    if (np->account.type == MUTT_ACCT_TYPE_IMAP && np->fd >= 0)
    {
      TAILQ_REMOVE(head, np, entries);
      mutt_message(_("Closing connection to %s..."), np->account.host);
      imap_logout((struct ImapData **) (void *) &np->data);
      mutt_clear_error();
      mutt_socket_free(np);
    }
  }
}
