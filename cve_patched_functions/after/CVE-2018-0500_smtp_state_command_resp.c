static CURLcode smtp_state_command_resp(struct connectdata *conn, int smtpcode,
                                        smtpstate instate)
{
  CURLcode result = CURLE_OK;
  struct Curl_easy *data = conn->data;
  struct SMTP *smtp = data->req.protop;
  char *line = data->state.buffer;
  size_t len = strlen(line);

  (void)instate; /* no use for this yet */

  if((smtp->rcpt && smtpcode/100 != 2 && smtpcode != 553 && smtpcode != 1) ||
     (!smtp->rcpt && smtpcode/100 != 2 && smtpcode != 1)) {
    failf(data, "Command failed: %d", smtpcode);
    result = CURLE_RECV_ERROR;
  }
  else {
    /* Temporarily add the LF character back and send as body to the client */
    if(!data->set.opt_no_body) {
      line[len] = '\n';
      result = Curl_client_write(conn, CLIENTWRITE_BODY, line, len + 1);
      line[len] = '\0';
    }

    if(smtpcode != 1) {
      if(smtp->rcpt) {
        smtp->rcpt = smtp->rcpt->next;

        if(smtp->rcpt) {
          /* Send the next command */
          result = smtp_perform_command(conn);
        }
        else
          /* End of DO phase */
          state(conn, SMTP_STOP);
      }
      else
        /* End of DO phase */
        state(conn, SMTP_STOP);
    }
  }

  return result;
}
