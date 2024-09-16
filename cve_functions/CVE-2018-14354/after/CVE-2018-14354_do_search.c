static int do_search(const struct Pattern *search, int allpats)
{
  int rc = 0;
  const struct Pattern *pat = NULL;

  for (pat = search; pat; pat = pat->next)
  {
    switch (pat->op)
    {
      case MUTT_BODY:
      case MUTT_HEADER:
      case MUTT_WHOLE_MSG:
        if (pat->stringmatch)
          rc++;
        break;
      case MUTT_SERVERSEARCH:
        rc++;
        break;
      default:
        if (pat->child && do_search(pat->child, 1))
          rc++;
    }

    if (!allpats)
      break;
  }

  return rc;
}
