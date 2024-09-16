keyval_get(struct keyval *kv, const char *name)
{
  struct onekeyval *okv;

  if (!kv)
    return NULL;

  for (okv = kv->head; okv; okv = okv->next)
    {
      if (strcasecmp(okv->name, name) == 0)
        return okv->value;
    }

  return NULL;
}
