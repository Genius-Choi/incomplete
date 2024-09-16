rend_service_is_ephemeral(const struct rend_service_t *s)
{
  return (s->directory == NULL);
}
