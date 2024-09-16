md5_state_update (struct md5_state *s, void *data, size_t len)
{
  md_ctx_update(&s->ctx, data, len);
}
