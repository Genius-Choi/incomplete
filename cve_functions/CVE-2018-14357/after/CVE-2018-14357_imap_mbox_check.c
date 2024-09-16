static int imap_mbox_check(struct Context *ctx, int *index_hint)
{
  int rc;
  (void) index_hint;

  imap_allow_reopen(ctx);
  rc = imap_check(ctx->data, 0);
  imap_disallow_reopen(ctx);

  return rc;
}
