keyval_alloc(void)
{
  struct keyval *kv;

  kv = calloc(1, sizeof(struct keyval));
  if (!kv)
    {
      DPRINTF(E_LOG, L_MISC, "Out of memory for keyval alloc\n");

      return NULL;
    }

  return kv;
}
