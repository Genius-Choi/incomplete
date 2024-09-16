static json_t *parse_array(lex_t *lex, size_t flags, json_error_t *error)
{
    json_t *array = json_array();
    if(!array)
        return NULL;

    lex_scan(lex, error);
    if(lex->token == ']')
        return array;

    while(lex->token) {
        json_t *elem = parse_value(lex, flags, error);
        if(!elem)
            goto error;

        if(json_array_append(array, elem)) {
            json_decref(elem);
            goto error;
        }
        json_decref(elem);

        lex_scan(lex, error);
        if(lex->token != ',')
            break;

        lex_scan(lex, error);
    }

    if(lex->token != ']') {
        error_set(error, lex, "']' expected");
        goto error;
    }

    return array;

error:
    json_decref(array);
    return NULL;
}
