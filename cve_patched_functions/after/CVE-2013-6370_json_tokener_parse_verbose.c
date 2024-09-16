struct json_object* json_tokener_parse_verbose(const char *str, enum json_tokener_error *error)
{
    struct json_tokener* tok;
    struct json_object* obj;

    tok = json_tokener_new();
    if (!tok)
      return NULL;
    obj = json_tokener_parse_ex(tok, str, -1);
    *error = tok->err;
    if(tok->err != json_tokener_success) {
		if (obj != NULL)
			json_object_put(obj);
        obj = NULL;
    }

    json_tokener_free(tok);
    return obj;
}
