void pop_fetch_mail(void)
{
  char buffer[LONG_STRING];
  char msgbuf[SHORT_STRING];
  char *url = NULL, *p = NULL;
  int delanswer, last = 0, msgs, bytes, rset = 0, ret;
  struct Connection *conn = NULL;
  struct Context ctx;
  struct Message *msg = NULL;
  struct Account acct;
  struct PopData *pop_data = NULL;

  if (!PopHost)
  {
    mutt_error(_("POP host is not defined."));
    return;
  }

  url = p = mutt_mem_calloc(strlen(PopHost) + 7, sizeof(char));
  if (url_check_scheme(PopHost) == U_UNKNOWN)
  {
    strcpy(url, "pop://");
    p = strchr(url, '\0');
  }
  strcpy(p, PopHost);

  ret = pop_parse_path(url, &acct);
  FREE(&url);
  if (ret)
  {
    mutt_error(_("%s is an invalid POP path"), PopHost);
    return;
  }

  conn = mutt_conn_find(NULL, &acct);
  if (!conn)
    return;

  pop_data = mutt_mem_calloc(1, sizeof(struct PopData));
  pop_data->conn = conn;

  if (pop_open_connection(pop_data) < 0)
  {
    mutt_socket_free(pop_data->conn);
    FREE(&pop_data);
    return;
  }

  conn->data = pop_data;

  mutt_message(_("Checking for new messages..."));

  /* find out how many messages are in the mailbox. */
  mutt_str_strfcpy(buffer, "STAT\r\n", sizeof(buffer));
  ret = pop_query(pop_data, buffer, sizeof(buffer));
  if (ret == -1)
    goto fail;
  if (ret == -2)
  {
    mutt_error("%s", pop_data->err_msg);
    goto finish;
  }

  sscanf(buffer, "+OK %d %d", &msgs, &bytes);

  /* only get unread messages */
  if (msgs > 0 && PopLast)
  {
    mutt_str_strfcpy(buffer, "LAST\r\n", sizeof(buffer));
    ret = pop_query(pop_data, buffer, sizeof(buffer));
    if (ret == -1)
      goto fail;
    if (ret == 0)
      sscanf(buffer, "+OK %d", &last);
  }

  if (msgs <= last)
  {
    mutt_message(_("No new mail in POP mailbox."));
    goto finish;
  }

  if (mx_mbox_open(NONULL(Spoolfile), MUTT_APPEND, &ctx) == NULL)
    goto finish;

  delanswer = query_quadoption(PopDelete, _("Delete messages from server?"));

  snprintf(msgbuf, sizeof(msgbuf),
           ngettext("Reading new messages (%d byte)...",
                    "Reading new messages (%d bytes)...", bytes),
           bytes);
  mutt_message("%s", msgbuf);

  for (int i = last + 1; i <= msgs; i++)
  {
    msg = mx_msg_open_new(&ctx, NULL, MUTT_ADD_FROM);
    if (!msg)
      ret = -3;
    else
    {
      snprintf(buffer, sizeof(buffer), "RETR %d\r\n", i);
      ret = pop_fetch_data(pop_data, buffer, NULL, fetch_message, msg->fp);
      if (ret == -3)
        rset = 1;

      if (ret == 0 && mx_msg_commit(&ctx, msg) != 0)
      {
        rset = 1;
        ret = -3;
      }

      mx_msg_close(&ctx, &msg);
    }

    if (ret == 0 && delanswer == MUTT_YES)
    {
      /* delete the message on the server */
      snprintf(buffer, sizeof(buffer), "DELE %d\r\n", i);
      ret = pop_query(pop_data, buffer, sizeof(buffer));
    }

    if (ret == -1)
    {
      mx_mbox_close(&ctx, NULL);
      goto fail;
    }
    if (ret == -2)
    {
      mutt_error("%s", pop_data->err_msg);
      break;
    }
    if (ret == -3)
    {
      mutt_error(_("Error while writing mailbox!"));
      break;
    }

    /* L10N: The plural is picked by the second numerical argument, i.e.
     * the %d right before 'messages', i.e. the total number of messages. */
    mutt_message(ngettext("%s [%d of %d message read]",
                          "%s [%d of %d messages read]", msgs - last),
                 msgbuf, i - last, msgs - last);
  }

  mx_mbox_close(&ctx, NULL);

  if (rset)
  {
    /* make sure no messages get deleted */
    mutt_str_strfcpy(buffer, "RSET\r\n", sizeof(buffer));
    if (pop_query(pop_data, buffer, sizeof(buffer)) == -1)
      goto fail;
  }

finish:
  /* exit gracefully */
  mutt_str_strfcpy(buffer, "QUIT\r\n", sizeof(buffer));
  if (pop_query(pop_data, buffer, sizeof(buffer)) == -1)
    goto fail;
  mutt_socket_close(conn);
  FREE(&pop_data);
  return;

fail:
  mutt_error(_("Server closed connection!"));
  mutt_socket_close(conn);
  FREE(&pop_data);
}
