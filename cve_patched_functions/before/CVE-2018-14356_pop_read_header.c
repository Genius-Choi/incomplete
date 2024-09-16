static int pop_read_header(struct PopData *pop_data, struct Header *h)
{
  int rc, index;
  size_t length;
  char buf[LONG_STRING];

  FILE *f = mutt_file_mkstemp();
  if (!f)
  {
    mutt_perror("mutt_file_mkstemp failed!");
    return -3;
  }

  snprintf(buf, sizeof(buf), "LIST %d\r\n", h->refno);
  rc = pop_query(pop_data, buf, sizeof(buf));
  if (rc == 0)
  {
    sscanf(buf, "+OK %d %zu", &index, &length);

    snprintf(buf, sizeof(buf), "TOP %d 0\r\n", h->refno);
    rc = pop_fetch_data(pop_data, buf, NULL, fetch_message, f);

    if (pop_data->cmd_top == 2)
    {
      if (rc == 0)
      {
        pop_data->cmd_top = 1;

        mutt_debug(1, "set TOP capability\n");
      }

      if (rc == -2)
      {
        pop_data->cmd_top = 0;

        mutt_debug(1, "unset TOP capability\n");
        snprintf(pop_data->err_msg, sizeof(pop_data->err_msg), "%s",
                 _("Command TOP is not supported by server."));
      }
    }
  }

  switch (rc)
  {
    case 0:
    {
      rewind(f);
      h->env = mutt_rfc822_read_header(f, h, 0, 0);
      h->content->length = length - h->content->offset + 1;
      rewind(f);
      while (!feof(f))
      {
        h->content->length--;
        fgets(buf, sizeof(buf), f);
      }
      break;
    }
    case -2:
    {
      mutt_error("%s", pop_data->err_msg);
      break;
    }
    case -3:
    {
      mutt_error(_("Can't write header to temporary file!"));
      break;
    }
  }

  mutt_file_fclose(&f);
  return rc;
}
