raptor_rss_sax2_new_namespace_handler(void *user_data,
                                      raptor_namespace* nspace)
{
  raptor_parser* rdf_parser = (raptor_parser*)user_data;
  raptor_rss_parser* rss_parser;
  int n;
  
  rss_parser = (raptor_rss_parser*)rdf_parser->context;
  for(n = 0; n < RAPTOR_RSS_NAMESPACES_SIZE; n++) {
    raptor_uri* ns_uri = rdf_parser->world->rss_namespaces_info_uris[n];
    if(!ns_uri)
      continue;
    
    if(!raptor_uri_equals(ns_uri, nspace->uri)) {
       rss_parser->nspaces_seen[n] = 'Y';
       break;
    }
  }

}
