static void lex_free_string(lex_t *lex)
{
    jsonp_free(lex->value.string.val);
    lex->value.string.val = NULL;
    lex->value.string.len = 0;
}
