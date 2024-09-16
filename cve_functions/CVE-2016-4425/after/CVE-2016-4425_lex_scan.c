static int lex_scan(lex_t *lex, json_error_t *error)
{
    int c;

    strbuffer_clear(&lex->saved_text);

    if(lex->token == TOKEN_STRING)
        lex_free_string(lex);

    do
        c = lex_get(lex, error);
    while(c == ' ' || c == '\t' || c == '\n' || c == '\r');

    if(c == STREAM_STATE_EOF) {
        lex->token = TOKEN_EOF;
        goto out;
    }

    if(c == STREAM_STATE_ERROR) {
        lex->token = TOKEN_INVALID;
        goto out;
    }

    lex_save(lex, c);

    if(c == '{' || c == '}' || c == '[' || c == ']' || c == ':' || c == ',')
        lex->token = c;

    else if(c == '"')
        lex_scan_string(lex, error);

    else if(l_isdigit(c) || c == '-') {
        if(lex_scan_number(lex, c, error))
            goto out;
    }

    else if(l_isalpha(c)) {
        /* eat up the whole identifier for clearer error messages */
        const char *saved_text;

        do
            c = lex_get_save(lex, error);
        while(l_isalpha(c));
        lex_unget_unsave(lex, c);

        saved_text = strbuffer_value(&lex->saved_text);

        if(strcmp(saved_text, "true") == 0)
            lex->token = TOKEN_TRUE;
        else if(strcmp(saved_text, "false") == 0)
            lex->token = TOKEN_FALSE;
        else if(strcmp(saved_text, "null") == 0)
            lex->token = TOKEN_NULL;
        else
            lex->token = TOKEN_INVALID;
    }

    else {
        /* save the rest of the input UTF-8 sequence to get an error
           message of valid UTF-8 */
        lex_save_cached(lex);
        lex->token = TOKEN_INVALID;
    }

out:
    return lex->token;
}
