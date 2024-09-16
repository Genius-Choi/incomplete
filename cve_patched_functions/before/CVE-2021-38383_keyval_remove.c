keyval_remove(struct keyval *kv, const char *name)
{
  struct onekeyval *okv;
  struct onekeyval *pokv;

  if (!kv)
    return;

  for (pokv = NULL, okv = kv->head; okv; pokv = okv, okv = okv->next)
    {
      if (strcasecmp(okv->name, name) == 0)
        break;
    }

  if (!okv)
    return;

  if (okv == kv->head)
    kv->head = okv->next;

  if (okv == kv->tail)
    kv->tail = pokv;

  if (pokv)
    pokv->next = okv->next;

  free(okv->name);
  free(okv->value);
  free(okv);
}
