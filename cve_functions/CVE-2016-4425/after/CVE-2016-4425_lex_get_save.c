static int lex_get_save(lex_t *lex, json_error_t *error)
{
    int c = stream_get(&lex->stream, error);
    if(c != STREAM_STATE_EOF && c != STREAM_STATE_ERROR)
        lex_save(lex, c);
    return c;
}
