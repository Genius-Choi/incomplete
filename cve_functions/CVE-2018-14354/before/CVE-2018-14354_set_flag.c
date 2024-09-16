static void set_flag(struct ImapData *idata, int aclbit, int flag,
                     const char *str, char *flags, size_t flsize)
{
  if (mutt_bit_isset(idata->ctx->rights, aclbit))
    if (flag && imap_has_flag(&idata->flags, str))
      mutt_str_strcat(flags, flsize, str);
}
