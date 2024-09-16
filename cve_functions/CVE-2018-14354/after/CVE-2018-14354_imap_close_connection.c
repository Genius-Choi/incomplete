void imap_close_connection(struct ImapData *idata)
{
  if (idata->state != IMAP_DISCONNECTED)
  {
    mutt_socket_close(idata->conn);
    idata->state = IMAP_DISCONNECTED;
  }
  idata->seqno = idata->nextcmd = idata->lastcmd = idata->status = false;
  memset(idata->cmds, 0, sizeof(struct ImapCommand) * idata->cmdslots);
}
