int imap_cmd_start(struct ImapData *idata, const char *cmdstr)
{
  return cmd_start(idata, cmdstr, 0);
}
