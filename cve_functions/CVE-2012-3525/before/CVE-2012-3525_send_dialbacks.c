void send_dialbacks(conn_t out)
{
  char *rkey;
  int rkeylen;

  if (out->s2s->dns_bad_timeout > 0) {
      dnsres_t bad = xhash_get(out->s2s->dns_bad, out->key);

      if (bad != NULL) {
          log_debug(ZONE, "removing bad host entry for '%s'", out->key);
          xhash_zap(out->s2s->dns_bad, out->key);
          free(bad->key);
          free(bad);
      }
  }

  if (xhash_iter_first(out->routes)) {
       log_debug(ZONE, "sending dialback packets for %s", out->key);
       do {
            xhash_iter_get(out->routes, (const char **) &rkey, &rkeylen, NULL);
            _out_dialback(out, rkey, rkeylen);
          } while(xhash_iter_next(out->routes));
  }

  return;
}
