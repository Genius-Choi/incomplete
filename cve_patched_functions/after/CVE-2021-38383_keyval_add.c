keyval_add(struct keyval *kv, const char *name, const char *value)
{
  return keyval_add_size(kv, name, value, strlen(value));
}
