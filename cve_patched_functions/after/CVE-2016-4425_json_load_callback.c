json_t *json_load_callback(json_load_callback_t callback, void *arg, size_t flags, json_error_t *error)
{
    lex_t lex;
    json_t *result;

    callback_data_t stream_data;

    memset(&stream_data, 0, sizeof(stream_data));
    stream_data.callback = callback;
    stream_data.arg = arg;

    jsonp_error_init(error, "<callback>");

    if (callback == NULL) {
        error_set(error, NULL, "wrong arguments");
        return NULL;
    }

    if(lex_init(&lex, (get_func)callback_get, flags, &stream_data))
        return NULL;

    result = parse_json(&lex, flags, error);

    lex_close(&lex);
    return result;
}
