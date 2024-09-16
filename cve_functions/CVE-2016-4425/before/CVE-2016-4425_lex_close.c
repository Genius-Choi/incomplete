static void lex_close(lex_t *lex)
{
    if(lex->token == TOKEN_STRING)
        lex_free_string(lex);
    strbuffer_close(&lex->saved_text);
}
