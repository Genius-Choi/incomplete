static void cmd_handle_fatal(struct ImapData *idata)
{
  idata->status = IMAP_FATAL;

  if ((idata->state >= IMAP_SELECTED) && (idata->reopen & IMAP_REOPEN_ALLOW))
  {
    mx_fastclose_mailbox(idata->ctx);
    mutt_socket_close(idata->conn);
    mutt_error(_("Mailbox %s@%s closed"), idata->conn->account.login,
               idata->conn->account.host);
    idata->state = IMAP_DISCONNECTED;
  }

  imap_close_connection(idata);
  if (!idata->recovering)
  {
    idata->recovering = true;
    if (imap_conn_find(&idata->conn->account, 0))
      mutt_clear_error();
    idata->recovering = false;
  }
}
