void av_register_codec_parser(AVCodecParser *parser)
{
    do {
        parser->next = av_first_parser;
    } while (parser->next != avpriv_atomic_ptr_cas((void * volatile *)&av_first_parser, parser->next, parser));
}
