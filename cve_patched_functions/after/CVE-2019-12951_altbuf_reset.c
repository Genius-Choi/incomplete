MG_INTERNAL void altbuf_reset(struct altbuf *ab) {
  mbuf_free(&ab->m);
  ab->len = 0;
}
