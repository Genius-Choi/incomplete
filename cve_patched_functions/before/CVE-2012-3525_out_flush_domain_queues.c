void out_flush_domain_queues(s2s_t s2s, const char *domain) {
  char *rkey;
  int rkeylen;
  char *c;
  int c_len;

  if (xhash_iter_first(s2s->outq)) {
      do {
          xhash_iter_get(s2s->outq, (const char **) &rkey, &rkeylen, NULL);
          c = memchr(rkey, '/', rkeylen);
          c++;
          c_len = rkeylen - (c - rkey);
          if (strncmp(domain, c, c_len) == 0)
              out_flush_route_queue(s2s, rkey, rkeylen);
      } while(xhash_iter_next(s2s->outq));
  }
}
