raptor_rss_parser_register_factory(raptor_parser_factory *factory) 
{
  int rc = 0;

  factory->desc.names = rss_tag_soup_names;

  factory->desc.mime_types = rss_tag_soup_types;

  factory->desc.label = "RSS Tag Soup";
  factory->desc.uri_strings = NULL;

  factory->desc.flags = RAPTOR_SYNTAX_NEED_BASE_URI;
  
  factory->context_length     = sizeof(raptor_rss_parser);
  
  factory->init      = raptor_rss_parse_init;
  factory->terminate = raptor_rss_parse_terminate;
  factory->start     = raptor_rss_parse_start;
  factory->chunk     = raptor_rss_parse_chunk;
  factory->recognise_syntax = raptor_rss_parse_recognise_syntax;

  return rc;
}
