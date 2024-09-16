static int lex_scan_number(lex_t *lex, int c, json_error_t *error)
{
    const char *saved_text;
    char *end;
    double doubleval;

    lex->token = TOKEN_INVALID;

    if(c == '-')
        c = lex_get_save(lex, error);

    if(c == '0') {
        c = lex_get_save(lex, error);
        if(l_isdigit(c)) {
            lex_unget_unsave(lex, c);
            goto out;
        }
    }
    else if(l_isdigit(c)) {
        do
            c = lex_get_save(lex, error);
        while(l_isdigit(c));
    }
    else {
        lex_unget_unsave(lex, c);
        goto out;
    }

    if(!(lex->flags & JSON_DECODE_INT_AS_REAL) &&
       c != '.' && c != 'E' && c != 'e')
    {
        json_int_t intval;

        lex_unget_unsave(lex, c);

        saved_text = strbuffer_value(&lex->saved_text);

        errno = 0;
        intval = json_strtoint(saved_text, &end, 10);
        if(errno == ERANGE) {
            if(intval < 0)
                error_set(error, lex, "too big negative integer");
            else
                error_set(error, lex, "too big integer");
            goto out;
        }

        assert(end == saved_text + lex->saved_text.length);

        lex->token = TOKEN_INTEGER;
        lex->value.integer = intval;
        return 0;
    }

    if(c == '.') {
        c = lex_get(lex, error);
        if(!l_isdigit(c)) {
            lex_unget(lex, c);
            goto out;
        }
        lex_save(lex, c);

        do
            c = lex_get_save(lex, error);
        while(l_isdigit(c));
    }

    if(c == 'E' || c == 'e') {
        c = lex_get_save(lex, error);
        if(c == '+' || c == '-')
            c = lex_get_save(lex, error);

        if(!l_isdigit(c)) {
            lex_unget_unsave(lex, c);
            goto out;
        }

        do
            c = lex_get_save(lex, error);
        while(l_isdigit(c));
    }

    lex_unget_unsave(lex, c);

    if(jsonp_strtod(&lex->saved_text, &doubleval)) {
        error_set(error, lex, "real number overflow");
        goto out;
    }

    lex->token = TOKEN_REAL;
    lex->value.real = doubleval;
    return 0;

out:
    return -1;
}
