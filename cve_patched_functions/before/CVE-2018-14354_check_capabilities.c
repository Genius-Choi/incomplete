static int check_capabilities(struct ImapData *idata)
{
  if (imap_exec(idata, "CAPABILITY", 0) != 0)
  {
    imap_error("check_capabilities", idata->buf);
    return -1;
  }

  if (!(mutt_bit_isset(idata->capabilities, IMAP4) ||
        mutt_bit_isset(idata->capabilities, IMAP4REV1)))
  {
    mutt_error(
        _("This IMAP server is ancient. NeoMutt does not work with it."));
    return -1;
  }

  return 0;
}
