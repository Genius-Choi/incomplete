raptor_rdfxml_record_ID(raptor_parser *rdf_parser,
                        raptor_rdfxml_element *element,
                        const unsigned char *id)
{
  raptor_rdfxml_parser *rdf_xml_parser;
  raptor_uri* base_uri;
  size_t id_len;
  int rc;
  
  rdf_xml_parser = (raptor_rdfxml_parser*)rdf_parser->context;

  if(!RAPTOR_OPTIONS_GET_NUMERIC(rdf_parser, RAPTOR_OPTION_CHECK_RDF_ID))
    return 0;

  base_uri = raptor_rdfxml_inscope_base_uri(rdf_parser);

  id_len = strlen((const char*)id);

  rc = raptor_id_set_add(rdf_xml_parser->id_set, base_uri, id, id_len);

  return (rc != 0);
}
