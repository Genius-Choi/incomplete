raptor_rdfxml_parser_stats_print(raptor_rdfxml_parser* rdf_xml_parser, 
                                 FILE *stream)
{
  fputs("rdf:ID set ", stream);
  raptor_id_set_stats_print(rdf_xml_parser->id_set, stream);
}
