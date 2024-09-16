struct NntpData *mutt_newsgroup_subscribe(struct NntpServer *nserv, char *group)
{
  struct NntpData *nntp_data = NULL;

  if (!nserv || !nserv->groups_hash || !group || !*group)
    return NULL;

  nntp_data = nntp_data_find(nserv, group);
  nntp_data->subscribed = true;
  if (!nntp_data->newsrc_ent)
  {
    nntp_data->newsrc_ent = mutt_mem_calloc(1, sizeof(struct NewsrcEntry));
    nntp_data->newsrc_len = 1;
    nntp_data->newsrc_ent[0].first = 1;
    nntp_data->newsrc_ent[0].last = 0;
  }
  return nntp_data;
}
