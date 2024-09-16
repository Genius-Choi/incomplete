raptor_rdfxml_parser_register_factory(raptor_parser_factory *factory) 
{
  int rc = 0;

  factory->desc.names = rdfxml_names;

  factory->desc.mime_types = rdfxml_types;

  factory->desc.label = "RDF/XML";
  factory->desc.uri_strings = rdfxml_uri_strings;

  factory->desc.flags = RAPTOR_SYNTAX_NEED_BASE_URI;
  
  factory->context_length     = sizeof(raptor_rdfxml_parser);
  
  factory->init      = raptor_rdfxml_parse_init;
  factory->terminate = raptor_rdfxml_parse_terminate;
  factory->start     = raptor_rdfxml_parse_start;
  factory->chunk     = raptor_rdfxml_parse_chunk;
  factory->finish_factory = raptor_rdfxml_parse_finish_factory;
  factory->recognise_syntax = raptor_rdfxml_parse_recognise_syntax;

  return rc;
}
