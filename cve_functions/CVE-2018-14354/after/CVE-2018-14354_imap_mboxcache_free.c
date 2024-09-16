void imap_mboxcache_free(struct ImapData *idata)
{
  struct ImapStatus *status = NULL;

  struct ListNode *np;
  STAILQ_FOREACH(np, &idata->mboxcache, entries)
  {
    status = (struct ImapStatus *) np->data;
    FREE(&status->name);
  }

  mutt_list_free(&idata->mboxcache);
}
