struct json_tokener* json_tokener_new_ex(int depth)
{
  struct json_tokener *tok;

  tok = (struct json_tokener*)calloc(1, sizeof(struct json_tokener));
  if (!tok) return NULL;
  tok->stack = (struct json_tokener_srec *)calloc(depth, sizeof(struct json_tokener_srec));
  if (!tok->stack) {
    free(tok);
    return NULL;
  }
  tok->pb = printbuf_new();
  tok->max_depth = depth;
  json_tokener_reset(tok);
  return tok;
}
