static int imap_msg_open_new(struct Context *ctx, struct Message *msg, struct Header *hdr)
{
  char tmp[PATH_MAX];

  mutt_mktemp(tmp, sizeof(tmp));
  msg->fp = mutt_file_fopen(tmp, "w");
  if (!msg->fp)
  {
    mutt_perror(tmp);
    return -1;
  }
  msg->path = mutt_str_strdup(tmp);
  return 0;
}
