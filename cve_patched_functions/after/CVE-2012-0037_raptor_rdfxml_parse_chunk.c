raptor_rdfxml_parse_chunk(raptor_parser* rdf_parser,
                          const unsigned char *buffer,
                          size_t len, int is_end) 
{
  raptor_rdfxml_parser* rdf_xml_parser;
  int rc;
  
  rdf_xml_parser = (raptor_rdfxml_parser*)rdf_parser->context;
  if(rdf_parser->failed)
    return 1;

  rc = raptor_sax2_parse_chunk(rdf_xml_parser->sax2, buffer, len, is_end);

  if(is_end) {
    if(rdf_parser->emitted_default_graph) {
      raptor_parser_end_graph(rdf_parser, NULL, 0);
      rdf_parser->emitted_default_graph--;
    }
  }

  return rc;
}
