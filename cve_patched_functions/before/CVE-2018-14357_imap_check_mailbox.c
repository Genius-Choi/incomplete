int imap_check_mailbox(struct Context *ctx, int force)
{
  return imap_check(ctx->data, force);
}
