json_t *json_loads(const char *string, size_t flags, json_error_t *error)
{
    lex_t lex;
    json_t *result;
    string_data_t stream_data;

    jsonp_error_init(error, "<string>");

    if (string == NULL) {
        error_set(error, NULL, "wrong arguments");
        return NULL;
    }

    stream_data.data = string;
    stream_data.pos = 0;

    if(lex_init(&lex, string_get, flags, (void *)&stream_data))
        return NULL;

    result = parse_json(&lex, flags, error);

    lex_close(&lex);
    return result;
}
