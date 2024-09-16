void json_tokener_free(struct json_tokener *tok)
{
  json_tokener_reset(tok);
  if (tok->pb) printbuf_free(tok->pb);
  if (tok->stack) free(tok->stack);
  free(tok);
}
