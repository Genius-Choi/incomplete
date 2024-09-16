int imap_read_literal(FILE *fp, struct ImapData *idata, unsigned long bytes,
                      struct Progress *pbar)
{
  char c;
  bool r = false;
  struct Buffer *buf = NULL;

  if (DebugLevel >= IMAP_LOG_LTRL)
    buf = mutt_buffer_alloc(bytes + 10);

  mutt_debug(2, "reading %ld bytes\n", bytes);

  for (unsigned long pos = 0; pos < bytes; pos++)
  {
    if (mutt_socket_readchar(idata->conn, &c) != 1)
    {
      mutt_debug(1, "error during read, %ld bytes read\n", pos);
      idata->status = IMAP_FATAL;

      mutt_buffer_free(&buf);
      return -1;
    }

    if (r && c != '\n')
      fputc('\r', fp);

    if (c == '\r')
    {
      r = true;
      continue;
    }
    else
      r = false;

    fputc(c, fp);

    if (pbar && !(pos % 1024))
      mutt_progress_update(pbar, pos, -1);
    if (DebugLevel >= IMAP_LOG_LTRL)
      mutt_buffer_addch(buf, c);
  }

  if (DebugLevel >= IMAP_LOG_LTRL)
  {
    mutt_debug(IMAP_LOG_LTRL, "\n%s", buf->data);
    mutt_buffer_free(&buf);
  }
  return 0;
}
