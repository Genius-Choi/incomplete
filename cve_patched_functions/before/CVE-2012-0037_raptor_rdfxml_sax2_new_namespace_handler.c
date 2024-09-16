raptor_rdfxml_sax2_new_namespace_handler(void *user_data,
                                         raptor_namespace* nspace)
{
  raptor_parser* rdf_parser;
  const unsigned char* namespace_name;
  size_t namespace_name_len;
  raptor_uri* uri = raptor_namespace_get_uri(nspace);

  rdf_parser = (raptor_parser*)user_data;
  raptor_parser_start_namespace(rdf_parser, nspace);

  if(!uri)
    return;
  
  namespace_name = raptor_uri_as_counted_string(uri, &namespace_name_len);
  
  if(namespace_name_len == raptor_rdf_namespace_uri_len-1 && 
     !strncmp((const char*)namespace_name, 
              (const char*)raptor_rdf_namespace_uri, 
              namespace_name_len)) {
    const unsigned char *prefix = raptor_namespace_get_prefix(nspace);
    raptor_parser_warning(rdf_parser,
                          "Declaring a namespace with prefix %s to URI %s - one letter short of the RDF namespace URI and probably a mistake.",
                          prefix, namespace_name);
  } 

  if(namespace_name_len > raptor_rdf_namespace_uri_len && 
     !strncmp((const char*)namespace_name,
              (const char*)raptor_rdf_namespace_uri,
              raptor_rdf_namespace_uri_len)) {
    raptor_parser_error(rdf_parser,
                        "Declaring a namespace URI %s to which the RDF namespace URI is a prefix is forbidden.",
                        namespace_name);
  }
}
