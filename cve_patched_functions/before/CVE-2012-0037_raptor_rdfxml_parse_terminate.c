raptor_rdfxml_parse_terminate(raptor_parser *rdf_parser) 
{
  raptor_rdfxml_parser* rdf_xml_parser;
  raptor_rdfxml_element* element;
  int i;

  rdf_xml_parser = (raptor_rdfxml_parser*)rdf_parser->context;

  if(rdf_xml_parser->sax2) {
    raptor_free_sax2(rdf_xml_parser->sax2);
    rdf_xml_parser->sax2 = NULL;
  }
  
  while( (element = raptor_rdfxml_element_pop(rdf_xml_parser)) )
    raptor_free_rdfxml_element(element);


  for(i = 0; i < RAPTOR_RDFXML_N_CONCEPTS; i++) {
    raptor_uri* concept_uri = rdf_xml_parser->concepts[i];
    if(concept_uri) {
      raptor_free_uri(concept_uri);
      rdf_xml_parser->concepts[i] = NULL;
    }
  }
  
  if(rdf_xml_parser->id_set) {
    raptor_free_id_set(rdf_xml_parser->id_set);
    rdf_xml_parser->id_set = NULL;
  }

}
