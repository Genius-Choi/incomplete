static int lex_init(lex_t *lex, get_func get, size_t flags, void *data)
{
    stream_init(&lex->stream, get, data);
    if(strbuffer_init(&lex->saved_text))
        return -1;

    lex->flags = flags;
    lex->token = TOKEN_INVALID;
    return 0;
}
