static char *lex_steal_string(lex_t *lex, size_t *out_len)
{
    char *result = NULL;
    if(lex->token == TOKEN_STRING) {
        result = lex->value.string.val;
        *out_len = lex->value.string.len;
        lex->value.string.val = NULL;
        lex->value.string.len = 0;
    }
    return result;
}
