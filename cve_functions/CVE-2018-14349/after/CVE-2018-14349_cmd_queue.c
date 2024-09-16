static int cmd_queue(struct ImapData *idata, const char *cmdstr, int flags)
{
  if (cmd_queue_full(idata))
  {
    mutt_debug(3, "Draining IMAP command pipeline\n");

    const int rc = imap_exec(idata, NULL, IMAP_CMD_FAIL_OK | (flags & IMAP_CMD_POLL));

    if (rc < 0 && rc != -2)
      return rc;
  }

  struct ImapCommand *cmd = cmd_new(idata);
  if (!cmd)
    return IMAP_CMD_BAD;

  if (mutt_buffer_printf(idata->cmdbuf, "%s %s\r\n", cmd->seq, cmdstr) < 0)
    return IMAP_CMD_BAD;

  return 0;
}
