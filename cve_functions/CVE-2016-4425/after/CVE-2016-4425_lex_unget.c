static void lex_unget(lex_t *lex, int c)
{
    stream_unget(&lex->stream, c);
}
