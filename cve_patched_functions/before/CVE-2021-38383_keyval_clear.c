keyval_clear(struct keyval *kv)
{
  struct onekeyval *hokv;
  struct onekeyval *okv;

  if (!kv)
    return;

  hokv = kv->head;

  for (okv = hokv; hokv; okv = hokv)
    {
      hokv = okv->next;

      free(okv->name);
      free(okv->value);
      free(okv);
    }

  kv->head = NULL;
  kv->tail = NULL;
}
