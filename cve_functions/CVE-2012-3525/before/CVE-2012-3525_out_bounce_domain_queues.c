int out_bounce_domain_queues(s2s_t s2s, const char *domain, int err)
{
  char *rkey;
  int rkeylen;
  int pktcount = 0;

  if (xhash_iter_first(s2s->outq)) {
      do {
          xhash_iter_get(s2s->outq, (const char **) &rkey, &rkeylen, NULL);
          if(s2s_route_key_match(NULL, (char *) domain, rkey, rkeylen))
              pktcount += out_bounce_route_queue(s2s, rkey, rkeylen, err);
      } while(xhash_iter_next(s2s->outq));
  }

  return pktcount;
}
