static bool compare_flags_for_copy(struct Header *h)
{
  struct ImapHeaderData *hd = (struct ImapHeaderData *) h->data;

  if (h->read != hd->read)
    return true;
  if (h->old != hd->old)
    return true;
  if (h->flagged != hd->flagged)
    return true;
  if (h->replied != hd->replied)
    return true;

  return false;
}
