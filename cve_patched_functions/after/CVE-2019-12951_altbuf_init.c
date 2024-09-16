MG_INTERNAL void altbuf_init(struct altbuf *ab, char *buf, size_t buf_size) {
  mbuf_init(&ab->m, 0);
  ab->user_buf = buf;
  ab->user_buf_size = buf_size;
  ab->len = 0;
}
