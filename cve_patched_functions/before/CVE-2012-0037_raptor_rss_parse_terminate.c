raptor_rss_parse_terminate(raptor_parser *rdf_parser)
{
  raptor_rss_parser *rss_parser = (raptor_rss_parser*)rdf_parser->context;
  int n;
  
  if(rss_parser->sax2)
    raptor_free_sax2(rss_parser->sax2);

  raptor_rss_model_clear(&rss_parser->model);

  for(n = 0; n < RAPTOR_RSS_NAMESPACES_SIZE; n++) {
    if(rss_parser->nspaces[n])
      raptor_free_namespace(rss_parser->nspaces[n]);
  }

  if(rss_parser->nstack)
    raptor_free_namespaces(rss_parser->nstack);

  raptor_rss_common_terminate(rdf_parser->world);
}
