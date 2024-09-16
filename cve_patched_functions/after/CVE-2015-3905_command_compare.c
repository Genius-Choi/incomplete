static int CDECL command_compare(const void *key, const void *item)
{
  return strcmp((const char *) key, ((const struct command *) item)->name);
}
