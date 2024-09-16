void nntp_group_unread_stat(struct NntpData *nntp_data)
{
  nntp_data->unread = 0;
  if (nntp_data->last_message == 0 || nntp_data->first_message > nntp_data->last_message)
    return;

  nntp_data->unread = nntp_data->last_message - nntp_data->first_message + 1;
  for (unsigned int i = 0; i < nntp_data->newsrc_len; i++)
  {
    anum_t first = nntp_data->newsrc_ent[i].first;
    if (first < nntp_data->first_message)
      first = nntp_data->first_message;
    anum_t last = nntp_data->newsrc_ent[i].last;
    if (last > nntp_data->last_message)
      last = nntp_data->last_message;
    if (first <= last)
      nntp_data->unread -= last - first + 1;
  }
}
